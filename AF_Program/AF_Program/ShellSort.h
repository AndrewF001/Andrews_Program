#pragma once
#include "SortingTemplateClass.h"
class ShellSort :
    public SortingTemplateClass
{
public:
	ShellSort(Menu1* parent, unsigned int arrsize);
	~ShellSort();

private:
	void AlgorithmMethod();

};

