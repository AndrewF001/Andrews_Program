#include "SortingTemplateClass.h"


SortingTemplateClass::SortingTemplateClass(QObject *parent, unsigned int arrsize) : TabTemplateClass(parent)
{
	ArrSize = arrsize;
	Arr = new int[ArrSize];
}

SortingTemplateClass::~SortingTemplateClass()
{
	delete[] Arr;
}

bool SortingTemplateClass::ChangeSize(int i)
{
	return false;
}

void SortingTemplateClass::Randomize()
{
	if (State == RunState::Restarted)
	{
		Arr = new int[ArrSize];
		for (int i = 0; i < ArrSize; i++)
		{
			Arr[i] = i+1;
		}
	}
}
