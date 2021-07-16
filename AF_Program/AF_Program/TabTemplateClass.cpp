#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(QObject *parent)
	: QObject(nullptr)
{
	DelayMS = &((TabClass*)parent)->Delay; //distgusting!!! Just links the int to the int in the tab for the delay interval
	ThisStopwatch = new StopWatch();
	Timer1 = new QTimer(this);
	Timer2 = new QTimer(this);
}

TabTemplateClass::~TabTemplateClass()
{
	delete ThisStopwatch;

}

bool TabTemplateClass::ExitQuerry()
{
	if (Request == RunRequest::Close || Request == RunRequest::Pause || Request == RunRequest::Stop || Request == RunRequest::Restart)
		return true;
	return false;
}