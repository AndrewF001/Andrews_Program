#include "BubbleSort.h"

BubbleSort::BubbleSort(QObject* parent, unsigned int arrsize) : SortingTemplateClass(parent, arrsize)
{
	AlgrothimName = "Bubble";
}

BubbleSort::~BubbleSort()
{

}

void BubbleSort::AlgorithmMethod()
{
	bool swap = true;
	for (int i=0;i < Arr.size(); i++)
	{
		if (!swap)
			break;
		swap = false;
		Index1 = 0;
		for (Index2 = 1;Index2 < Arr.size()-i; Index1 = Index2++)
		{
			ThreadProcess;
			if (Arr[Index1] > Arr[Index2])
			{
				SwapPos(Index1, Index2);
				swap = true;
			}
		}
	}
}
