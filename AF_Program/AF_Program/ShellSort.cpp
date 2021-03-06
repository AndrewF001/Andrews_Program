#include "ShellSort.h"

ShellSort::ShellSort(Menu1* parent, unsigned int arrsize) : SortingTemplateClass(parent, arrsize)
{
	AlgrothimName = "Shell";
}

ShellSort::~ShellSort()
{

}

void ShellSort::AlgorithmMethod()
{
    for (int gap = Arr.size() / 2; gap > 0; gap /= 2)
    {
        for (Index1 = gap; Index1 < Arr.size(); Index1++)
        {
            unsigned int temp = Arr[Index1];

            for (Index2 = Index1; Index2 >= gap && Arr[Index2-gap] > temp; Index2 -= gap)
            {
                Comparisons++;
                Swaps++;
                Arr[Index2] = Arr[Index2 - gap];
                ThreadProcess;
            }
            Comparisons++;
            Arr[Index2] = temp;
            ThreadProcess;
        }
    }


}