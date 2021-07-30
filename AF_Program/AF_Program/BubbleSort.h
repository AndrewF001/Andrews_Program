#pragma once
#include "SortingTemplateClass.h"

class BubbleSort : public SortingTemplateClass
{
public:
	BubbleSort(QObject* parent, unsigned int arrsize);
	~BubbleSort();

private:
	void AlgorithmMethod();

	
};

