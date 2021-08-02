#pragma once
#include "SortingTemplateClass.h"
class ShellSort :
    public SortingTemplateClass
{
public:
	ShellSort(TabClass* parent, unsigned int arrsize);
	~ShellSort();

private:
	void AlgorithmMethod();

};

