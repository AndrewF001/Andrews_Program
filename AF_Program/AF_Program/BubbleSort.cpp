#include "BubbleSort.h"

BubbleSort::BubbleSort(QObject* parent, unsigned int arrsize) : SortingTemplateClass(parent, arrsize)
{
	AlgrothimName = "Bubble";
}

BubbleSort::~BubbleSort()
{

}

void BubbleSort::Start()
{
	int x = 1;
	while (true)
	{
		QCoreApplication::processEvents();
	}
	int y;
}

void BubbleSort::Stop()
{
	int x;
}

void BubbleSort::Reset()
{
	int x;
	emit ArrayPing(Arr, -1, -1);
	emit TitlePing(0, 0, 0);
}

//void BubbleSort::Cancle()
//{
//
//}