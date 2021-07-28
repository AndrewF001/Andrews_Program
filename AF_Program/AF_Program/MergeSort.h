#pragma once
#include "SortingTemplateClass.h"
class MergeSort :
    public SortingTemplateClass
{
	//Q_OBJECT	
public:
	MergeSort(QObject* parent, unsigned int arrsize);
	~MergeSort();

private:
	void AlgorithmMethod();

};

