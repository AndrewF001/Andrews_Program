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

bool TabTemplateClass::ProcessEventLoop()
{
	ThisStopwatch->Pause();

	QThread::msleep(*DelayMS);
	QCoreApplication::sendPostedEvents();

	if (Request == RunRequest::Close || Request == RunRequest::Restart)
		return true;

	if (Request == RunRequest::Pause)
	{
		while (Request != RunRequest::Run)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			if (Request == RunRequest::Close || Request == RunRequest::Restart)
				return true;
		}
	}
	ThisStopwatch->Start();
	return false;
}