#include "MergeSort.h"


MergeSort::MergeSort(Menu1* parent, unsigned int arrsize) : SortingTemplateClass(parent, arrsize)
{
	AlgrothimName = "Merge";
	GFPTR = &Static_SGF::GraphicsMethod2;
}

MergeSort::~MergeSort()
{

}
//merge sort done with iteration
//this method needs to be split up to make it more readable
void MergeSort::AlgorithmMethod()
{
	int Gap = 1;										//Size of sub array
	int Loops = std::ceil(std::log2(Arr.size()));		//mathamatically work out how many runs through are required
	int Divisions = std::ceil(Arr.size() / 2);			//How many groups of 2 are in the current layer
	int Count1 = 0, Count2 = 0, Count3 = 0;				//count1 = pos in left arr, count2 = pos in right arr, count3 is size of combined arr, this is required if the arrsize isn't a power of 2
	const int ArrSize = Arr.size();						
	std::vector<int> TempArr;							//couldn't get int* arr[] to work as error occured when delete[]
	TempArr.resize(ArrSize);							//so went for vector :/
	for (int i = 0; i < Loops; i++)						//first iteration
	{
		for (int j = 0; j < Divisions; j++)				//each division
		{
			Index1 = j * (Gap *2);						//left sub array index
			Index2 = Index1 + Gap;						//right sub array index
			Range1 = Index1;							//graphical work
			Range2 = Index2 + Gap - 1;
			Count1 = 0;									//reset variables
			Count2 = 0;
			Count3 = 0;
			if (Index2 >= ArrSize)						//this is for if there is a odd ammounts of groups, bassically makes it skip the while loop
				Count2 = Gap * 2;
			while (Count2 + Count1 != Gap*2)			//Uses count2 + count1 with the condition checks to bassically do a calculated recusion
			{
				Comparisons++;
				if ((Count2!=Gap && Arr[Index1] > Arr[Index2])||(Count1==Gap))	//Most versions of iterative Merge sort split up the for and while part of the code but I merged them, that's why I have the or gate
				{
					TempArr[Count3] = Arr[Index2];
					Count2++;
					Index2++;
					if (Index2 == ArrSize)				//edge case
						Count2 = Gap;
				}
				else
				{
					TempArr[Count3] = Arr[Index1];
					Count1++;
					Index1++;
					if (Index1 == j * Gap * 2 + Gap)	//edge case
						Count1 = Gap;
				}
				Count3++;								//count3 needs to be different from count1 + count2 if it reaches a edge case
				ThreadProcess;							//run macro
			}
			Index2 = -1;								//only require 1 line on the GUI
			Index1 = j * (Gap * 2);						//go back to the start of the area
			for (int i = 0; i < Count3; i++)			//this is why Count3 was needed overwise overflow 
			{
				Swaps++;
				Arr[Index1] = TempArr[i];				//copy the TempArr to actual array
				ThreadProcess;							//show visually
				Index1++;								//only then can you increment
			}
		}
		Gap = Gap * 2;									//increase Gap size
		Divisions = std::ceil(ArrSize / ((double)Gap * 2));//work out new number of devisions, has to be re-calculated because of std::ceil
	}
}

std::vector<unsigned int> MergeSort::SerilizedData()
{
	std::vector<unsigned int> output;
	output.resize(Arr.size() + 4);
	output[0] = Index1;
	output[1] = Index2;
	output[2] = Range1;
	output[3] = Range2;
	for (int i = 4; i < Arr.size() + 4; i++)
	{
		output[i] = Arr[i - 4];
	}
	return output;
}