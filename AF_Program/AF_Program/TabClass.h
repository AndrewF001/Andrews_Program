#pragma once
#include "TabUI.h"
#include <qwidget.h>

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class TabClass
{

public:
	TabClass(QWidget*);
	~TabClass();

	TabUI* ThisTab = nullptr;
	QString Name;	
	QWidget* ParentPTR;	//may not be nessecary
};

