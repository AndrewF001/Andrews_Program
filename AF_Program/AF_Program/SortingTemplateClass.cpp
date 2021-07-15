#include "SortingTemplateClass.h"
#include "SortingBaseClass.h"

SortingTemplateClass::SortingTemplateClass(QObject *parent, unsigned int arrsize) : TabTemplateClass(parent)
{
	ChangeSize(arrsize);
	connect(Timer1, &QTimer::timeout, this, &SortingTemplateClass::FrameRate1);
	Timer1->setSingleShot(6);//144hz
	connect(Timer2, &QTimer::timeout, this, &SortingTemplateClass::FrameRate2);
	Timer2->setSingleShot(16);//60hz
}

SortingTemplateClass::~SortingTemplateClass()
{

}

int SortingTemplateClass::ArrSize()
{
	return Arr.size();
}

void SortingTemplateClass::ChangeSize(int i)
{
	if (i != Arr.size())
	{
		Arr.resize(i);
		ResetArr();
		IntialArr = Arr;
	}
}

void SortingTemplateClass::Randomize()
{
	std::srand(time(NULL));
	for (int i = Arr.size()-1; i > 0; i--)
	{
		int j = rand() % (i+1);
		SwapPos(i,j);
	}
	IntialArr = Arr;
}

void SortingTemplateClass::SwapPos(int ind1, int ind2)
{
	int temp = Arr[ind1];
	Arr[ind1] = Arr[ind2];
	Arr[ind2] = temp;
}

void SortingTemplateClass::ResetArr()
{
	for (int i = 0; i < Arr.size(); i++)
	{
		Arr[i] = i + 1;
	}
}

bool SortingTemplateClass::ExitQuerry()
{
	return TabTemplateClass::ExitQuerry();
}

void SortingTemplateClass::Shuffle(int size)
{
	ChangeSize(size);
	Randomize();
	RenderMethod();
}

void SortingTemplateClass::FrameRate1()
{
	if (!ExitQuerry())
	{
		emit ArrayPing(Arr, Index1, Index2);
		Timer1->start();
	}
}

void SortingTemplateClass::FrameRate2()
{
	if (!ExitQuerry())
	{
		emit TitlePing(ThisStopwatch->Duration(), Comparisons, Swaps);
		Timer2->start();
	}
}


void SortingTemplateClass::RenderMethod()
{
	emit ArrayPing(Arr, -1, -1);
	emit TitlePing(ThisStopwatch->Duration(), Comparisons, Swaps);
}