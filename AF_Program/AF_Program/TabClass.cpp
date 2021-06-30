#include "TabClass.h"

TabClass::TabClass(QWidget *Parent)
{
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

