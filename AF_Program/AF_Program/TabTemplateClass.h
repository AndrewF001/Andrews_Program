#pragma once

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <chrono>
#include "RunStateEnum.h"
#include "StopWatch.h"
#include "TabClass.h"
#define	ThreadProcess \
if (ProcessEventLoop()){return;} \

/*
This Class is the worker thread template. Every single worker thread must inherit it because it hold the 6 basic signal/slots that are required to work with
TabUI which every tab inherits
*/

class TabTemplateClass : public QObject
{
	Q_OBJECT

public slots:					//corrosonding RequestEnum slot
	void Start() ;	//run
	void Pause();	//pause
	void Reset();	//restart
	void Cancle();	//close

signals:
	void Finished();
	void Error(); 


public:
	QString AlgrothimName;
	RunState State = RunState::Restarted;
	RunRequest Request = RunRequest::Pause;
	unsigned int *DelayMS;
	bool Debug_Mode = false;	
	StopWatch *ThisStopwatch;
	QTimer *Timer1, *Timer2;

	TabTemplateClass(QObject *parent);
	~TabTemplateClass();

protected:
	bool ProcessEventLoop();
	virtual void RenderMethod() = 0;
	virtual void TemplateStart() = 0;
	virtual void TemplatePause() = 0;
	virtual void TemplateReset() = 0;
	virtual void TemplateCancle() = 0;

	virtual void AlgorithmMethod() = 0;

private:
	bool TryRequestState(RunRequest);
};
