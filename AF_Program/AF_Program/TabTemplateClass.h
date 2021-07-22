#pragma once

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <chrono>
#include "RunStateEnum.h"
#include "StopWatch.h"
#include "TabClass.h"
/*
This Class is the worker thread template. Every single worker thread must inherit it because it hold the 6 basic signal/slots that are required to work with
TabUI which every tab inherits
*/

class TabTemplateClass : public QObject
{
	Q_OBJECT

public slots:					//corrosonding RequestEnum slot
	virtual void Start() = 0;	//run
	virtual void Pause() = 0;	//pause
	virtual void Reset() = 0;	//restart
	virtual void Cancle() = 0;	//close

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
};
