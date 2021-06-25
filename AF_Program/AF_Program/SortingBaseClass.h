#pragma once
#include "TabClass.h"
#include "SortingTemplateClass.h"
#include "qwidget.h"

/*
	extends TabClass so that it can communicate sorting related specific singal/slot with SortingTemplateClass
*/
class SortingBaseClass : public TabClass
{
public:
	SortingBaseClass(QWidget *);
	virtual ~SortingBaseClass();

private:
	std::vector<SortingTemplateClass*> Algorithms;


};

