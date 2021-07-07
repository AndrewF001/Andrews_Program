#pragma once
#include "TabTemplateClass.h"


/*
	This will hold all the signal and slots that are required to communicate with SortingBaseClass
	This is inherited by the actual sorting class that does the work.
*/
class SortingTemplateClass : public TabTemplateClass
{
	Q_OBJECT
public:
	//unsigned int ArrSize = 30;

	SortingTemplateClass(QObject *parent, unsigned int arrsize);
	~SortingTemplateClass();
	bool ChangeSize(int);
	int ArrSize();

private:
	std::vector<unsigned int> Arr;
	int Comparisons = 0, Swaps = 0;
	QTimer* Timer1;
	QTimer* Timer2;
	void Randomize();

public slots:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;
	void Shuffle(int);
	//virtual void Cancle() = 0;
	void FrameRate1();
	void FrameRate2();

signals:
	void TitlePing(std::chrono::duration<double, std::milli> Timer, int Comparison, int Swaps);
	void ArrayPing(std::vector<unsigned int>, int, int);
};

