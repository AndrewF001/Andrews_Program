#pragma once
#include "TabTemplateClass.h"
Q_DECLARE_METATYPE(std::vector<unsigned int>);

/*
	This will hold all the signal and slots that are required to communicate with SortingBaseClass
	This is inherited by the actual sorting class that does the work.
*/
class SortingTemplateClass : public TabTemplateClass
{
	Q_OBJECT;
public:
	//unsigned int ArrSize = 30;

	SortingTemplateClass(QObject *parent, unsigned int arrsize);
	~SortingTemplateClass();
	int ArrSize();

protected:
	std::vector<unsigned int> Arr;
	std::vector<unsigned int> IntialArr;
	int Comparisons = 0, Swaps = 0;
	int Index1, Index2;
	void SwapPos(int, int);
	void RenderMethod();
	bool ProcessEventLoop();
	virtual void AlgorithmMethod()=0;


private:
	void Randomize();
	void ResetArr();
	void ChangeSize(int);

public slots:
	void Start();
	void Pause();
	void Reset();
	void Cancle();
	void Shuffle(int);
	void FrameRate1();
	void FrameRate2();

signals:
	void TitlePing(long long Timer, int Comparison, int Swaps);
	void ArrayPing(QVariant arr, int index1, int index2);
};

