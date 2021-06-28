#pragma once
#include "TabClass.h"
#include "SortingTemplateClass.h"
#include "qwidget.h"
#include "QtCore"
#include "QtGui"

/*
	extends TabClass so that it can communicate sorting related specific singal/slot with SortingTemplateClass
*/
class SortingBaseClass : public TabClass
{
	Q_OBJECT

public:
	SortingBaseClass(QWidget *);
	virtual ~SortingBaseClass();
	
public slots:
	void PrimaryBtnClicked();

private:
	std::vector<SortingTemplateClass*> Algorithms;
};

