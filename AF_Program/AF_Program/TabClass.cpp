#include "TabClass.h"

TabClass::TabClass(QWidget *Parent, int i)
{
	index = i;
	ParentPTR = Parent;
	ThisTab = new TabUI(ParentPTR);
	SetConnection();
}

TabClass::~TabClass()
{
	ThisTab->close();
	delete ThisTab;
}

void TabClass::SetConnection()
{
	connect(ThisTab->ui.PrimaryBtn, &QPushButton::clicked, this, &TabClass::PrimaryBtnClicked);
	connect(ThisTab->ui.SecondaryBtn, &QPushButton::clicked, this, &TabClass::SecondaryBtnClicked);	
	connect(ThisTab->ui.AlgoComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &TabClass::AlgoComboBoxChanged);
	connect(ThisTab->ui.DelaySpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &TabClass::DelaySpinBox);
}

void TabClass::DelaySpinBox(int value)
{
	Delay = value;
}

void TabClass::TabChanged(int i)
{
	if (i == index && !Active)
	{
		Active = true;
		OpenTab();
	}
	else if(i!=index && Active)
	{
		Active = false;
		CloseTab();
	}
}

void TabClass::SetStartState()
{
	ThisState = TabState::start;
	ThisTab->ui.AlgoComboBox->setEnabled(true);
	ThisTab->ui.TimerLab->setText("0");
	ThisTab->ui.PrimaryBtn->setText("Start");
}

void TabClass::SetRunningState()
{
	ThisState = TabState::running;
	ThisTab->ui.AlgoComboBox->setEnabled(false);
	ThisTab->ui.PrimaryBtn->setText("Pause");
}

void TabClass::SetPausedState()
{
	ThisState = TabState::paused;
	ThisTab->ui.PrimaryBtn->setText("Resume");
}

void TabClass::SetEndState()
{
	ThisState = TabState::ended;
	ThisTab->ui.AlgoComboBox->setEnabled(true);
	ThisTab->ui.PrimaryBtn->setText("Restart");
}






