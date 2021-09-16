#include "SortingTemplateClass.h"
#include "SortingBaseClass.h"

SortingTemplateClass::SortingTemplateClass(Menu1* parent,  unsigned int arrsize) : TabTemplateClass(parent)
{
	qRegisterMetaType<std::vector<unsigned int>>("QVariant"); //pass std::vector in a signal
	ChangeSize(arrsize);
	connect(Timer1, &QTimer::timeout, this, &SortingTemplateClass::FrameRate1);
	//Timer1->setSingleShot(6);//144hz
	Timer1->setInterval(6);
	connect(Timer2, &QTimer::timeout, this, &SortingTemplateClass::FrameRate2);
	//Timer2->setSingleShot(16);//60hz
	Timer2->setInterval(6);
}

SortingTemplateClass::~SortingTemplateClass()
{

}


void SortingTemplateClass::TemplateStart()
{

}

void SortingTemplateClass::TemplatePause()
{

}

void SortingTemplateClass::TemplateReset()
{
	Arr = IntialArr;
	Swaps = 0;
	Comparisons = 0;
	Index1 = -1;
	Index2 = -1;
	ThisStopwatch->Restart();
}

void SortingTemplateClass::TemplateCancle()
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


void SortingTemplateClass::SwapPos(int ind1,int ind2)
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

bool SortingTemplateClass::ProcessEventLoop()
{
	return TabTemplateClass::ProcessEventLoop();
}

void SortingTemplateClass::Shuffle(int size)
{
	ChangeSize(size);
	Randomize();
	RenderMethod();
}

void SortingTemplateClass::FrameRate1()
{
	if ((State == RunState::Running || State == RunState::Paused) && !*PaintEventActive)
	{
		SendArrayPing();
	}
}

void SortingTemplateClass::FrameRate2()
{
	if ((State == RunState::Running || State == RunState::Paused) && !*PaintEventActive)
	{
		emit TitlePing(ThisStopwatch->Duration(), Comparisons, Swaps);
	}
}


void SortingTemplateClass::RenderMethod()
{
	SendArrayPing();
	emit TitlePing(ThisStopwatch->Duration(), Comparisons, Swaps);
}


void SortingTemplateClass::SendArrayPing()
{
	QVariant Data;
	Data.setValue(SerilizedData());
	QVariant FPTR;
	FPTR.setValue(GFPTR);
	emit ArrayPing(Data, FPTR);
}

std::vector<unsigned int> SortingTemplateClass::SerilizedData()
{
	std::vector<unsigned int> output;
	output.resize(Arr.size() + 2);
	output[0] = Index1;
	output[1] = Index2;
	for (int i = 2; i < Arr.size()+2; i++)
	{
		output[i] = Arr[i - 2];
	}
	return output;
}