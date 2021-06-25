#pragma once
#include "TabUI.h"
#include <qwidget.h>

class TabClass
{

public:
	TabClass(QWidget*);
	~TabClass();

	TabUI* ThisTab = nullptr;
	QString Name;	
	QWidget* ParentPTR;	//may not be nessecary
};

