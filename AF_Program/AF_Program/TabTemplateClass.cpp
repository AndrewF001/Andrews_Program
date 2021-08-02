#include "TabTemplateClass.h"



TabTemplateClass::TabTemplateClass(TabClass *parent)
	: QObject(nullptr)
{
	DelayMS = &parent->Delay;
	PaintEventActive = &parent->InPaintEvent;
	ThisStopwatch = new StopWatch();
	Timer1 = new QTimer(this);
	Timer2 = new QTimer(this);
}

TabTemplateClass::~TabTemplateClass()
{
	delete ThisStopwatch;
	Timer1->stop();
	Timer2->stop();
}

//Just does security checks for in the request is valid
//doing backend instead of front end
bool TabTemplateClass::TryRequestState(RunRequest NewRequest)
{
	//could make switch statement but find this easier to read
	//won't comment each method but based on request the programme need to act accordingly
	if (NewRequest == RunRequest::Run)
	{
		Request = NewRequest;
		if (State == RunState::Restarted || State == RunState::Closed)
		{
			return true;
		}
	}
	else if (NewRequest == RunRequest::Pause)
	{
		if (State == RunState::Running)
		{
			Request = NewRequest;
			return true;
		}
	}
	else if (NewRequest == RunRequest::Restart)
	{
		Request = NewRequest;
		return true;
	}
	else if (NewRequest == RunRequest::Close)
	{
		Request = NewRequest;
		State = RunState::Closed;
		return true;
	}
	return false;
}

//This is the method that is responsiable for holding the programming, checking the event loop running and exit
//return values are true if the programme should stop, false if should carry on
bool TabTemplateClass::ProcessEventLoop()
{
	ThisStopwatch->Pause(); //gotta get accreate time measurements

	QThread::msleep(*DelayMS); //this is how I'm creating the delay
	QCoreApplication::sendPostedEvents(); //process events which will update Request
	//Will only process the most recent event! This can cause errors!

	if (Request == RunRequest::Close || Request == RunRequest::Restart)
		return true;

	if (Request == RunRequest::Pause) //if we require a pause, could make it's only method for readabilty
	{
		State = RunState::Paused;
		while (Request != RunRequest::Run)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(16)); //check every frame update, so it doesn't hog CPU time
			QCoreApplication::sendPostedEvents();
			if (Request == RunRequest::Close || Request == RunRequest::Restart)
				return true;
		}
	}

	State = RunState::Running;
	ThisStopwatch->Start();
	return false;
}


void TabTemplateClass::Start()
{
	if (TryRequestState(RunRequest::Run))
	{
		State = RunState::Running;
		Timer1->start();
		Timer2->start();
		ThisStopwatch->Restart();
		ThisStopwatch->Start();

		TemplateStart();
		AlgorithmMethod();

		ThisStopwatch->Pause();
		Timer1->stop();
		Timer2->stop();

		RenderMethod();
		if (State != RunState::Restarted || State != RunState::Closed)
		{
			emit Finished();
			TemplateReset();
			State = RunState::Restarted;
		}
	}
}

void TabTemplateClass::Pause()
{
	if (TryRequestState(RunRequest::Pause))
	{
		RenderMethod();
		TemplatePause();
	}
}

void TabTemplateClass::Reset()
{
	if (TryRequestState(RunRequest::Restart))
	{
		Timer1->stop();
		Timer2->stop();
		Request = RunRequest::Restart;
		RenderMethod();
		TemplateReset();
	}
}

void TabTemplateClass::Cancle()
{
	if (TryRequestState(RunRequest::Close))
	{
		Timer1->stop();
		Timer2->stop();
		Request = RunRequest::Close;
		RenderMethod();
		TemplateCancle();
	}
}