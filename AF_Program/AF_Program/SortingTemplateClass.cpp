#include "SortingTemplateClass.h"


SortingTemplateClass::SortingTemplateClass(QObject *parent, unsigned int arrsize) : TabTemplateClass(parent)
{
	ArrSize = arrsize;
	Arr = new int[ArrSize];
	Timer1 = new QTimer(this);
	Timer2 = new QTimer(this);
	connect(Timer1, &QTimer::timeout, this, &SortingTemplateClass::FrameRate1);
	connect(Timer2, &QTimer::timeout, this, &SortingTemplateClass::FrameRate2);
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

void SortingTemplateClass::FrameRate1()
{
	emit ArrayPing(Arr);
}

void SortingTemplateClass::FrameRate2()
{
	emit TitlePing(Duration, Comparisons, Swaps);
}
