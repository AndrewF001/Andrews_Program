#include "TabClass.h"

TabClass::TabClass(QWidget *Parent)
{
	ParentPTR = Parent;
	ThisTab = new TabUI(ParentPTR);
	ThisTab->ui.AlgoComboBox->addItem("Testing");
}

TabClass::~TabClass()
{
	ThisTab->close();
	delete ThisTab;
}