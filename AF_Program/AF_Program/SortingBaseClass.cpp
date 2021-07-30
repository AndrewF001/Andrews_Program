#include "SortingBaseClass.h"

SortingBaseClass::SortingBaseClass(QWidget *Parent,int i) : TabClass(Parent, i)
{
	//sorting only variables
	Name = "Sorting";
	LeftWidget = new SortingLeftTitleUi(this);
	RightWidget = new SortingRightTitleUi(this);
	//setup ui
	ThisTab->ui.LeftTitleWidget->setLayout(LeftWidget->ui.horizontalLayout); 
	ThisTab->ui.RightTitleWidget->setLayout(RightWidget->ui.horizontalLayout);
	LeftWidget->ui.SizeSpinBox->setValue(Size);

	connect(LeftWidget->ui.SizeSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &SortingBaseClass::SizeSpinboxChanged);
	connect(LeftWidget->ui.ShuffleBtn, &QPushButton::clicked, this, &SortingBaseClass::ShuffleBtnClicked);
	//algorithms that are used for this class
	AddAlgorithms();
	//setup algorithms
	for (int i = 0; i < Algorithms.size(); i++)
	{
		ThisTab->ui.AlgoComboBox->addItem(Algorithms[i]->AlgrothimName); //add to UI
		Algorithms[i]->moveToThread(&WorkerThread); //move to thread
		connect(this, &SortingBaseClass::Cancle, Algorithms[i], &SortingTemplateClass::Cancle, Qt::QueuedConnection); //set up deletion signal
	}

	WorkerThread.start(prior); //start thread

	CurrentAlgorithm = Algorithms[0];

	ChangeThreadObj(0); //connect only 1 object to the thread

	update();
}

//add your own class to the vector and create on heap, not stack
void SortingBaseClass::AddAlgorithms()
{
	Bubble = new BubbleSort(this, Size);
	Algorithms.push_back(Bubble);

	Merge = new MergeSort(this, Size);
	Algorithms.push_back(Merge);

	Shell = new ShellSort(this, Size);
	Algorithms.push_back(Shell);
}

SortingBaseClass::~SortingBaseClass()
{
	LeftWidget->deleteLater(); //free the heap
	RightWidget->deleteLater();

	emit Cancle(); //tell every object to get ready for deletion
	QThread::msleep(Delay*2); //need this delay because of thread safety of overlap, otherwise access memory out of space
	
	Bubble->deleteLater(); //delete the actual object
}

void SortingBaseClass::ChangeThreadObj(int index)
{
	emit Stop();
	disconnect(this, &SortingBaseClass::Start, CurrentAlgorithm, &SortingTemplateClass::Start);
	disconnect(this, &SortingBaseClass::Stop, CurrentAlgorithm, &SortingTemplateClass::Pause);
	disconnect(this, &SortingBaseClass::Restart, CurrentAlgorithm, &SortingTemplateClass::Reset);
	disconnect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::Finished, this, &SortingBaseClass::Finished);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender);
	//swap algorithm
	CurrentIndex = index;
	CurrentAlgorithm = Algorithms[CurrentIndex];
	//set the new connection
	connect(this, &SortingBaseClass::Start, CurrentAlgorithm, &SortingTemplateClass::Start, Qt::QueuedConnection);
	connect(this, &SortingBaseClass::Stop, CurrentAlgorithm, &SortingTemplateClass::Pause, Qt::QueuedConnection);
	connect(this, &SortingBaseClass::Restart, CurrentAlgorithm, &SortingTemplateClass::Reset, Qt::QueuedConnection);
	connect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &SortingTemplateClass::Finished, this, &SortingBaseClass::Finished, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender, Qt::QueuedConnection);
	emit Restart();
}

void SortingBaseClass::AlgoComboBoxChanged(int index)
{
	if (index != CurrentIndex) //check is required as setCurrentIndex will call this method and start an infinite loop
	{
		ChangeThreadObj(index);
		ThisTab->ui.AlgoComboBox->setCurrentIndex(CurrentIndex);
	}
}

void SortingBaseClass::SizeSpinboxChanged(int value)
{
	Size = value;
}

void SortingBaseClass::ShuffleBtnClicked()
{
	emit shuffle(Size);
}

void SortingBaseClass::ArrayRender(QVariant Array, int index1, int index2)
{
	CopyArr = Array.value<std::vector<unsigned int>>();
	Index1 = index1;
	Index2 = index2;
	update();
}

void SortingBaseClass::paintEvent(QPaintEvent* PEvent)
{
	QPainter paint(this);
	QPen Pen(Qt::black);
	QRect Rect;
	DrawDrawableArea(&paint, &Pen,&Rect);
	QBrush Brush(Qt::blue);
	paint.setBrush(Brush);
	DrawArrayUI(&paint, &Pen, &Brush, &Rect);
}

void SortingBaseClass::StatRender(long long Timer, int Comparison, int Swaps)
{
	ThisTab->ui.TimerLab->setText(QString::number(Timer));
	RightWidget->ui.ComparisonLab->setText(QString::number(Comparison));
	RightWidget->ui.SwapLab->setText(QString::number(Swaps));
}

void SortingBaseClass::DrawArrayUI(QPainter* Painter, QPen* Pen, QBrush* Brush ,QRect* Area)
{
	if (CopyArr.size() == 0)
		return;

	QRect KeyRect;
	int Start_X = Area->x() + 5;
	int Start_Y = Area->y() + Area->height() - 5;

	double Xspacing = 1;
	int width = std::floor((Area->width() - 10) / (CopyArr.size()));
	double height_mult = ((double)(Area->height()-10) / (double)(CopyArr.size()));
	if (width == 0)
	{
		width = 1;
		Xspacing = (Area->width() - 10) / (CopyArr.size() + 2);
	}

	for (int i = 0; i < CopyArr.size(); i++)
	{
		if (i == Index1 || i == Index2)
		{
			Pen->setColor(Qt::red);
			Brush->setColor(Qt::red);
		}
		Painter->setPen(*Pen);
		Painter->setBrush(*Brush);
		KeyRect = QRect(Start_X + i * width, Start_Y, width, -(CopyArr[i] * height_mult));
		Painter->drawRect(KeyRect);
		Pen->setColor(Qt::black);
		Brush->setColor(Qt::blue);
		Painter->setPen(*Pen);
		Painter->setBrush(*Brush);
	}

}

void SortingBaseClass::OpenTab()
{

}

void SortingBaseClass::CloseTab()
{

}

void SortingBaseClass::SetStartState()
{
	TabClass::SetStartState();
	LeftWidget->ui.SizeSpinBox->setEnabled(true);
	LeftWidget->ui.ShuffleBtn->setEnabled(true);
	RightWidget->ui.ComparisonLab->setText("0");
	RightWidget->ui.SwapLab->setText("0");
	Size = CurrentAlgorithm->ArrSize();
	LeftWidget->ui.SizeSpinBox->setValue(Size);
}

void SortingBaseClass::SetRunningState()
{
	TabClass::SetRunningState();
	LeftWidget->ui.SizeSpinBox->setEnabled(false);
	LeftWidget->ui.ShuffleBtn->setEnabled(false);
}

void SortingBaseClass::SetPausedState()
{
	TabClass::SetPausedState();
}

void SortingBaseClass::SetEndState()
{
	TabClass::SetEndState();
	LeftWidget->ui.SizeSpinBox->setEnabled(true);
	LeftWidget->ui.ShuffleBtn->setEnabled(true);
}