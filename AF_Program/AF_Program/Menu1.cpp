#include "Menu1.h"
#include "TabTemplateClass.h"

Menu1::Menu1(QWidget* Parent) : TabClass(Parent, true)
{
	ThisTab->ui.MenuScrollArea->setWidget(MenuObject);
	MenuObject->ui.DelaySpinBox->setValue(Delay);
	DebugCheckChanged(MenuObject->ui.DebugMode->checkState());
}

Menu1::~Menu1()
{
	emit Stop();
	WorkerThread.quit(); //Quit through the event loop
	WorkerThread.wait(); //wait for the thread to end
	ThisTab->deleteLater();

	emit CloseTextFiles();
}

void Menu1::SetConnection()
{
	connect(MenuObject->ui.PrimaryBtn, &QPushButton::clicked, this, &Menu1::PrimaryBtnClicked);
	connect(MenuObject->ui.SecondaryBtn, &QPushButton::clicked, this, &Menu1::SecondaryBtnClicked);
	connect(MenuObject->ui.TextFileBtn, &QPushButton::clicked, this, &Menu1::TextFileBtnClicked);
	connect(MenuObject->ui.AlgoComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &Menu1::AlgoComboBoxChanged);
	connect(MenuObject->ui.DelaySpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &Menu1::DelaySpinBox);
	connect(MenuObject->ui.DebugMode, &QCheckBox::stateChanged, this, &Menu1::DebugCheckChanged);
}

void Menu1::C_CACB()
{
	MenuObject->ui.DebugMode->setVisible(Debug_Option);
}

void Menu1::C_CACL(int i)
{
	MenuObject->ui.AlgoComboBox->addItem(Algorithms[i]->AlgrothimName); //add to UI
}

void Menu1::DelaySpinBox(int value)
{
	Delay = value;
}

void Menu1::PrimaryBtnClicked()
{
	switch (ThisState)
	{
	case(TabState::start):
		SetRunningState();
		emit Start();
		break;
	case(TabState::running):
		SetPausedState();
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

void Menu1::SecondaryBtnClicked()
{
	SetStartState();
	emit Restart();
}

void Menu1::AlgoComboBoxChanged(int index)
{
	if (index != CurrentIndex) //check is required as setCurrentIndex will call this method and start an infinite loop
	{
		ChangeThreadObj(index);
		MenuObject->ui.AlgoComboBox->setCurrentIndex(CurrentIndex);
	}
}


void Menu1::SetStartState()
{
	TabClass::SetStartState();
	MenuObject->ui.AlgoComboBox->setEnabled(true);
	MenuObject->ui.TimerLab->setText("0");
	MenuObject->ui.PrimaryBtn->setText("Start");
}

void Menu1::SetRunningState()
{
	TabClass::SetRunningState();
	MenuObject->ui.AlgoComboBox->setEnabled(false);
	MenuObject->ui.PrimaryBtn->setText("Pause");
}

void Menu1::SetPausedState()
{
	TabClass::SetPausedState();
	MenuObject->ui.PrimaryBtn->setText("Resume");
}

void Menu1::SetEndState()
{
	TabClass::SetEndState();
	MenuObject->ui.AlgoComboBox->setEnabled(true);
	MenuObject->ui.PrimaryBtn->setText("Restart");
}
