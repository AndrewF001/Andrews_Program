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
	SortingTemplateClass(QObject*);
	~SortingTemplateClass();


public slots:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;
	virtual void Cancle() = 0;


};

