#include "TabClass.h"

TabClass::TabClass()
{
	ThisTab = new TabTemplate();
	ThisTab->ui.AlgoComboBox->addItem("Testing");
}

TabClass::~TabClass()
{
	ThisTab->close();
	delete ThisTab;
}