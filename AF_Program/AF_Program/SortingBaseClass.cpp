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
		//check initalized
		//emit start
		//change button
		break;
	case(TabState::running):
		SetPausedState();
		//emit pause
		//change button
		break;
	case(TabState::paused):
		SetRunningState();
		//emit start
		//change button
		break;
	case(TabState::ended):
		SetStartState();
		//emit reset
		//reset variables
		//emit start
		break;
	}
}

void SortingBaseClass::SecondaryBtnClicked()
{
	SetStartState();
	//no checks needed
	//emit restart
}

void SortingBaseClass::AlgoComboBoxChanged(int index)
{
	//if (index != CurrentIndex) { 
		if (ThisState == TabState::ended || ThisState == TabState::start)
		{
			CurrentIndex = index;
			ChangeThreadObj();
		}
	//	else
	//	{
	//		ThisTab->ui.AlgoComboBox->setCurrentIndex(CurrentIndex);
	//	}
	//}
}

void SortingBaseClass::SizeSpinboxChanged(int value)
{
	Size = value;
}

void SortingBaseClass::ShuffleBtnClicked()
{
	int x = 1;
}

void SortingBaseClass::ArrayRender(int Array[])
{

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