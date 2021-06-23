#pragma once
#include "TabClass.h"
#include "SortingTemplateClass.h"
#include "qwidget.h"

class SortingBaseClass : public TabClass
{
public:
	SortingBaseClass(QWidget *);
	virtual ~SortingBaseClass();

private:
	std::vector<SortingTemplateClass*> Algorithms;


};

