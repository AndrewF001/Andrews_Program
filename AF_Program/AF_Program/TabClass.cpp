#include "TabClass.h"

TabClass::TabClass(QWidget *Parent)
{
	ParentPTR = Parent;
	ThisTab = new TabUI(ParentPTR);
	ThisTab->ui.AlgoComboBox->addItem("Testing");
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
}