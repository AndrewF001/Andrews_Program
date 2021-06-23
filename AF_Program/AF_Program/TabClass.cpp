#include "TabClass.h"

TabClass::TabClass(QWidget *Parent)
{
	ThisTab = new TabTemplate(Parent);
	ThisTab->ui.AlgoComboBox->addItem("Testing");
}

TabClass::~TabClass()
{
	ThisTab->close();
	delete ThisTab;
}