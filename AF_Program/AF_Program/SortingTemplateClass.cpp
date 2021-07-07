#include "SortingTemplateClass.h"


SortingTemplateClass::SortingTemplateClass(QObject *parent, unsigned int arrsize) : TabTemplateClass(parent)
{
	Arr.resize(arrsize);
	Timer1 = new QTimer(this);
	Timer2 = new QTimer(this);
	connect(Timer1, &QTimer::timeout, this, &SortingTemplateClass::FrameRate1);
	connect(Timer2, &QTimer::timeout, this, &SortingTemplateClass::FrameRate2);
}

SortingTemplateClass::~SortingTemplateClass()
{
	delete Timer1;
	delete Timer2;
}

int SortingTemplateClass::ArrSize()
{
	return Arr.size();
}

bool SortingTemplateClass::ChangeSize(int i)
{
	return false;
}

void SortingTemplateClass::Randomize()
{
	if (State == RunState::Restarted)
	{
		for (int i = 0; i < Arr.size(); i++)
		{
			Arr[i] = i+1;
		}
	}
}

void SortingTemplateClass::Shuffle(int size)
{
	ChangeSize(size);
	Randomize();
}

void SortingTemplateClass::FrameRate1()
{
	emit ArrayPing(Arr,0,1);
}

void SortingTemplateClass::FrameRate2()
{
	emit TitlePing(Duration, Comparisons, Swaps);
}
