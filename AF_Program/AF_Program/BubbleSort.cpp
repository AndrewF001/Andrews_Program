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
	Request = RunRequest::Run;
	Timer1->start();
	Timer2->start();
	for (;i < Arr.size(); i++)
	{
		if (!swap && Index1 == 0)
			break;
		swap = false;
		for (;Index1 < Arr.size()-i-1; Index1++)
		{
			Index2 = Index1+1;
			//std::this_thread::sleep_for(std::chrono::milliseconds(*DelayMS));
			//QThread::msleep(*DelayMS);
			QCoreApplication::processEvents();
			
			if (ExitQuerry())
				return;
			if (Arr[Index1] > Arr[Index2])
			{
				SwapPos(Index1, Index2);
				swap = true;
			}
		}
		Index1 = 0;
	}
	RenderMethod();
	emit Finished();
	Reset();
}

void BubbleSort::Stop()
{
	Request = RunRequest::Pause;
	RenderMethod();
}

void BubbleSort::Reset()
{
	Request = RunRequest::Restart;
	RenderMethod();
	swap = true;
	Index1 = 0;
	i = 0;
	Index2 = 0;
	Arr = IntialArr;
}

//void BubbleSort::Cancle()
//{
//
//}