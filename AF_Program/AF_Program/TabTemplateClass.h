#pragma once

#include <QObject>
#include "QtCore"
#include "QtGui"

/*
This Class is the worker thread template. Every single worker thread must inherit it because it hold the 6 basic signal/slots that are required to work with
TabUI which every tab inherits
*/

class TabTemplateClass : public QObject
{
	Q_OBJECT

public slots:
	void Start();
	void Stop();
	void Reset();
	void Cancle();

signals:
	void Finished();
	void Error();

public:
	TabTemplateClass(QObject *parent);
	~TabTemplateClass();
};
