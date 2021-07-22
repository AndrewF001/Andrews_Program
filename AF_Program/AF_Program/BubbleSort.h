#pragma once
#include "SortingTemplateClass.h"

class BubbleSort : public SortingTemplateClass
{
	Q_OBJECT	
public:
	BubbleSort(QObject* parent, unsigned int arrsize);
	~BubbleSort();

private:
	void AlgorithmMethod();

	
};

