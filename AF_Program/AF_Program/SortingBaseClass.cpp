#include "SortingBaseClass.h"

SortingBaseClass::SortingBaseClass(QWidget *Parent,int i) : TabClass(Parent, i)
{
	//sorting only variables
	Name = "Sorting";
	FileHeader = "Sort_";
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

	CallAfterConstructor();
}

//add your own class to the vector and create on heap, not stack
void SortingBaseClass::AddAlgorithms()
{
	Bubble = new BubbleSort(this, Size);
	AddAlgorithm<SortingTemplateClass*>(Bubble);

	Merge = new MergeSort(this, Size);
	AddAlgorithm<SortingTemplateClass*>(Merge);

	Shell = new ShellSort(this, Size);
	AddAlgorithm<SortingTemplateClass*>(Shell);
}

SortingBaseClass::~SortingBaseClass()
{
	LeftWidget->deleteLater(); //free the heap
	RightWidget->deleteLater();

	emit Cancle(); //tell every object to get ready for deletion
	QThread::msleep(Delay*2); //need this delay because of thread safety of overlap, otherwise access memory out of space
	
	Bubble->deleteLater(); //delete the actual object
}

void SortingBaseClass::CustomDisconnect(TabTemplateClass* CTab)
{
	SortingTemplateClass* CurrentAlgorithm = (SortingTemplateClass*)CTab;
	disconnect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender);
	disconnect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender);
}

void SortingBaseClass::CustomConnect(TabTemplateClass* CTab)
{
	SortingTemplateClass* CurrentAlgorithm = (SortingTemplateClass*)CTab;
	connect(this, &SortingBaseClass::shuffle, CurrentAlgorithm, &SortingTemplateClass::Shuffle, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &SortingTemplateClass::TitlePing, this, &SortingBaseClass::StatRender, Qt::QueuedConnection);
	connect(CurrentAlgorithm, &SortingTemplateClass::ArrayPing, this, &SortingBaseClass::ArrayRender, Qt::QueuedConnection);
}

void SortingBaseClass::SizeSpinboxChanged(int value)
{
	Size = value;
}

void SortingBaseClass::ShuffleBtnClicked()
{
	emit shuffle(Size);
}

void SortingBaseClass::ArrayRender(QVariant Array, QVariant ptr)
{
	CopyArr = Array.value<std::vector<unsigned int>>();
	Stored_GFPTR = ptr.value<FPTR>();
	update();
}

void SortingBaseClass::CustomPaintEvent(QPainter* Painter, QPen* Pen, QBrush* Brush,QRect* Rect)
{
	Brush->setColor(Qt::blue);
	Painter->setBrush(*Brush);
	if(Stored_GFPTR!=nullptr)
		Stored_GFPTR(Painter, Pen, Brush, Rect, &CopyArr);
	//DrawArrayUI(Painter, Pen, Brush, Rect);
}

void SortingBaseClass::StatRender(long long Timer, int Comparison, int Swaps)
{
	ThisTab->ui.TimerLab->setText(QString::number(Timer));
	RightWidget->ui.ComparisonLab->setText(QString::number(Comparison));
	RightWidget->ui.SwapLab->setText(QString::number(Swaps));
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
	Size = FetchCurrentAlgorithm<SortingTemplateClass*>()->ArrSize();
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