#include "MergeSort.h"


MergeSort::MergeSort(QObject* parent, unsigned int arrsize) : SortingTemplateClass(parent, arrsize)
{
	AlgrothimName = "Merge";
}

MergeSort::~MergeSort()
{

}
//merge sort done with iteration
void MergeSort::AlgorithmMethod()
{
	int Gap = 1;
	int Loops = std::floor(std::log2(Arr.size()));
	int Divisions = std::ceil(Arr.size() / 2);
	int Count1 = 0, Count2 = 0;
	const int ArrSize = Arr.size();
	int* TempArr = new int[ArrSize];
	for (int i = 0; i < Loops; i++)
	{
		for (int j = 0; j < Divisions; j++)
		{
			Index1 = j * (Gap *2);
			Index2 = Index1 + Gap;
			Count1 = 0;
			Count2 = 0;
			if (Index2 >= ArrSize)
				Count2 = Gap * 2;
			while (Count1+Count2 != Gap*2)
			{
				if ((Count2!=Gap && Arr[Index1] > Arr[Index2])||(Count1==Gap))
				{
					TempArr[Count1 + Count2] = Arr[Index2];
					Count2++;
					Index2++;
					if (Index2 == ArrSize)
						Count2 = Gap;
				}
				else
				{
					TempArr[Count1 + Count2] = Arr[Index1];
					Count1++;
					Index1++;
				}
				ThreadProcess;
			}	
			Index2 = -1;
			Index1 = Index1 = j * (Gap * 2);
			for (int i = 0; i < Gap * 2; i++)
			{
				if (Index1 == ArrSize)
					break;
				Arr[Index1] = TempArr[i];
				ThreadProcess;
				Index1++;
			}
		}
		Gap = std::pow(2,i+1);
		Divisions = std::ceil(ArrSize / ((double)Gap*2));
	}
	delete[] TempArr;
}