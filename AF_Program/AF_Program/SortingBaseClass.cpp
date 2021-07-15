#include "SortingBaseClass.h"

SortingBaseClass::SortingBaseClass(QWidget *Parent,int i) : TabClass(Parent, i)
{
	Name = "Sorting";
	LeftWidget = new SortingLeftTitleUi(this);
	RightWidget = new SortingRightTitleUi(this);


	ThisTab->ui.LeftTitleWidget->setLayout(LeftWidget->ui.horizontalLayout);
	ThisTab->ui.RightTitleWidget->setLayout(RightWidget->ui.horizontalLayout);

	connect(LeftWidget->ui.SizeSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &SortingBaseClass::SizeSpinboxChanged);
	connect(LeftWidget->ui.ShuffleBtn, &QPushButton::clicked, this, &SortingBaseClass::ShuffleBtnClicked);

	AddAlgorithms();

	for (int i = 0; i < Algorithms.size(); i++)
	{
		ThisTab->ui.AlgoComboBox->addItem(Algorithms[i]->AlgrothimName);
		Algorithms[i]->moveToThread(&WorkerThread); //move to thread
	}

	WorkerThread.start(prior); //start thread

	CurrentAlgorithm = Algorithms[0];

	ChangeThreadObj(0); //connect only 1 object to the thread

	update();
}

void SortingBaseClass::AddAlgorithms()
{
	Bubble = new BubbleSort(this, 30);
	Algorithms.push_back(Bubble);
}

SortingBaseClass::~SortingBaseClass()
{
	LeftWidget->deleteLater(); //free the heap
	RightWidget->deleteLater();
	delete Bubble;

	//delete LeftWidget;    //deletelater is perfered over delete
	//delete RightWidget;
}

bool SortingBaseClass::ChangeThreadObj(int index)
{
	emit Stop();	//todo: this will cause an error if the the thread is in a std::this_thread::sleep_for state
					//need to bring back the emit cancle for this method and destructor and then move the disconnect to the worker thread
	disconnect(this, &SortingBaseClass::Start, CurrentAlgorithm, &SortingTemplateClass::Start);
	disconnect(this, &SortingBaseClass::Stop, CurrentAlgorithm, &SortingTemplateClass::Stop);
	disconnect(this, &SortingBaseClass::Restart, CurrentAlgorithm, &SortingTemplateClass::Reset);
	disconnect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::Finished, this, &SortingBaseClass::Finished);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender);
	//swap algorithm
	CurrentIndex = index;
	CurrentAlgorithm = Algorithms[CurrentIndex];
	//set the new connection
	//connect(WorkerThread, &QThread::started, CurrentAlgorithm, &SortingTemplateClass::Start);
	connect(this, &SortingBaseClass::Start, CurrentAlgorithm, &SortingTemplateClass::Start);
	connect(this, &SortingBaseClass::Stop, CurrentAlgorithm, &SortingTemplateClass::Stop);
	connect(this, &SortingBaseClass::Restart, CurrentAlgorithm, &SortingTemplateClass::Reset);
	connect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle);
	connect(CurrentAlgorithm, &SortingTemplateClass::Finished, this, &SortingBaseClass::Finished);
	connect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender);
	connect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender);
	emit Restart();
	return true;
}

void SortingBaseClass::PrimaryBtnClicked()
{
	switch (ThisState)
	{
	case(TabState::start):
		SetRunningState();
		//todo check initalized
		emit Start();
		break;
	case(TabState::running):
		SetPausedState();	//should add an extra layour of security for when it's pausing, because overlap can happen.
		emit Stop();
		break;
	case(TabState::paused):
		SetRunningState();
		emit Start();
		break;
	case(TabState::ended):
		SetStartState();
		emit Restart();
		break;
	}
}

void SortingBaseClass::SecondaryBtnClicked()
{
	SetStartState();
	emit Restart();
}

void SortingBaseClass::AlgoComboBoxChanged(int index)
{
	if (index != CurrentIndex) {
		if (ThisState == TabState::ended || ThisState == TabState::start)
		{
			if (!ChangeThreadObj(index))
				ThisTab->ui.AlgoComboBox->setCurrentIndex(CurrentIndex);
		}
	}
}

void SortingBaseClass::Finished()
{
	SetEndState();
}

void SortingBaseClass::SizeSpinboxChanged(int value)
{
	Size = value;
}

void SortingBaseClass::ShuffleBtnClicked()
{
	emit shuffle(Size);
}

void SortingBaseClass::ArrayRender(std::vector<unsigned int>Array, int index1, int index2)
{
	CopyArr = Array;
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

	double spacing = 1;
	int width = std::floor((Area->width() - 10) / (CopyArr.size()));
	int height_mult = std::floor((Area->height()-10) / CopyArr.size());
	if (CopyArr.size() - 2 > Area->width() - 10)
	{
		width = 1;
		spacing = (Area->width() - 10) / (CopyArr.size() + 2);
	}

	for (int i = 0; i < CopyArr.size(); i++)
	{
		if (i == Index1 || i == Index2)
		{
			Pen->setColor(Qt::red);
			Brush->setColor(Qt::red);
		}
		KeyRect = QRect(Start_X + i * width, Start_Y, width, -(CopyArr[i] * height_mult));
		Painter->drawRect(KeyRect);
		Pen->setColor(Qt::black);
		Brush->setColor(Qt::blue);
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