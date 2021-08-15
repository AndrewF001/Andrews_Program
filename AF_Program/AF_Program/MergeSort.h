#pragma once
#include "SortingTemplateClass.h"
class MergeSort :
    public SortingTemplateClass
{
public:
	MergeSort(TabClass* parent, unsigned int arrsize);
	~MergeSort();
	void AlgoPaintEvent(QPainter*, QPen*, QBrush*, QRect*, unsigned char*) override;

private:
	void AlgorithmMethod();

};

