#pragma once
#include "UIClasses.h"
#include "TabClass.h"
#include "SortingTemplateClass.h"

class SortingBaseClass : public TabClass
{
public:
	SortingBaseClass();
	virtual ~SortingBaseClass();

private:
	std::vector<SortingTemplateClass*> Algorithms;


};

