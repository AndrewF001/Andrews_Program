#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(QObject *parent)
	: QObject(parent)
{
	ThisStopwatch = new StopWatch();
	Timer1 = new QTimer();
	Timer2 = new QTimer();
}

TabTemplateClass::~TabTemplateClass()
{
	delete ThisStopwatch;
	delete Timer1;
	delete Timer2;
}