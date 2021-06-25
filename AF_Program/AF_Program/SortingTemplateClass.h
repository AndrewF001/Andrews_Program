#pragma once
#include "QtCore"
#include "QtGui"

class SortingTemplateClass : QObject
{

public slots:
	void Start();
	void Stop();
	void Reset();
	void Cancle();

signals:
	void Finished();
	void Error();
	 
};

