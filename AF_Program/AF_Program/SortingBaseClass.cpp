#include "SortingBaseClass.h"

SortingBaseClass::SortingBaseClass(QWidget *Parent,int i) : TabClass(Parent, i)
{
	Name = "Sorting";
	LeftWidget = new SortingLeftTitleUi(ThisTab->ui.LeftTitleWidget);
	RightWidget = new SortingRightTitleUi(ThisTab->ui.RightTitleWidget);

	ThisTab->ui.LeftTitleWidget->setLayout(LeftWidget->ui.horizontalLayout);
	ThisTab->ui.RightTitleWidget->setLayout(RightWidget->ui.horizontalLayout);

	connect(LeftWidget->ui.SizeSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &SortingBaseClass::SizeSpinboxChanged);
	connect(LeftWidget->ui.ShuffleBtn, &QPushButton::clicked, this, &SortingBaseClass::ShuffleBtnClicked);
	
	AddAlgorithms();

	for (int i = 0; i < Algorithms.size(); i++)
	{
		ThisTab->ui.AlgoComboBox->addItem(Algorithms[i]->AlgrothimName);
		Algorithms[i]->moveToThread(WorkerThread);
	}
	ThisTab->ui.AlgoComboBox->addItem("Test");
	CurrentAlgorithm = Algorithms[0];
}

void SortingBaseClass::AddAlgorithms()
{
	Bubble = new BubbleSort(this, 30);
	Algorithms.push_back(Bubble);
}

SortingBaseClass::~SortingBaseClass()
{
	LeftWidget->close();
	RightWidget->close();
	delete Bubble;
	delete LeftWidget;
	delete RightWidget;
}

void SortingBaseClass::ChangeThreadObj()
{
	if (WorkerThread->isFinished())
	{

	}
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
		SetPausedState();
		emit Pause();
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
	if (ThisState == TabState::ended || ThisState == TabState::start)
	{
		CurrentIndex = index;
		ChangeThreadObj();
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
	//QPrinter
}

void SortingBaseClass::StatRender(std::chrono::duration<double, std::milli> Timer, int Comparison, int Swaps)
{
	ThisTab->ui.TimerLab->setText(QString::number(Timer.count()));
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