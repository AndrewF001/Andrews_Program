#pragma once
#include "SortingTemplateClass.h"
class MergeSort :
    public SortingTemplateClass
{
public:
	MergeSort(Menu1* parent, unsigned int arrsize);
	~MergeSort();

private:
	int Range1 = -1, Range2 = -1;
	void AlgorithmMethod();
	std::vector<unsigned int> SerilizedData();
};

