#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(QObject *parent)
	: QObject(parent)
{
	DelayMS = &((TabClass*)parent)->Delay; //distgusting!!! Just links the int to the int in the tab for the delay interval
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

bool TabTemplateClass::ExitQuerry()
{
	if (Request == RunRequest::Close || Request == RunRequest::Pause || Request == RunRequest::Stop || Request == RunRequest::Restart)
		return true;
	return false;
}