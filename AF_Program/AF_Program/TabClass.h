#pragma once
#include "TabTemplate.h"
#include <qwidget.h>

class TabClass
{

public:
	TabClass(QWidget*);
	~TabClass();
	TabTemplate* ThisTab = nullptr;
	QString Name;
};

