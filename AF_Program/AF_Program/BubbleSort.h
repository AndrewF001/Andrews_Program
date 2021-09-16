#pragma once
#include "SortingTemplateClass.h"


class BubbleSort : public SortingTemplateClass
{
public:
	BubbleSort(Menu1 *parent, unsigned int arrsize);
	~BubbleSort();

private:
	void AlgorithmMethod();

	
};

