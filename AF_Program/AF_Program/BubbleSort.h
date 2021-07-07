#pragma once
#include "SortingTemplateClass.h"

class BubbleSort : public SortingTemplateClass
{
	Q_OBJECT	
public:
	BubbleSort(QObject* parent, unsigned int arrsize);
	~BubbleSort();

public slots:
	void Start();
	void Stop();
	void Reset();
	//void Cancle();


};

