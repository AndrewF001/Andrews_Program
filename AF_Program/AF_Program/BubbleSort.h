#pragma once
#include "SortingTemplateClass.h"


class BubbleSort : public SortingTemplateClass
{
public:
	BubbleSort(TabClass *parent, unsigned int arrsize);
	~BubbleSort();

private:
	void AlgorithmMethod();

	
};

