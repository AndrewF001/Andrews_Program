#pragma once
#include "SortingTemplateClass.h"
class MergeSort :
    public SortingTemplateClass
{
public:
	MergeSort(TabClass* parent, unsigned int arrsize);
	~MergeSort();

private:
	void AlgorithmMethod();

};

