#pragma once
#include "TabUI.h"
#include <qwidget.h>
#include "QtCore"
#include "QtGui"
#include "RunStateEnum.h"

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class TabClass : public QWidget
{
	Q_OBJECT
public slots:
	virtual void PrimaryBtnClicked() = 0;
	virtual void SecondaryBtnClicked() = 0;
	virtual void AlgoComboBoxChanged(int) = 0;
	virtual void Finished() = 0;
	void DelaySpinBox(int); 
	void TabChanged(int);

signals:
	void Start();
	void Stop();
	void Restart();

private: 
	int index;
	bool Active = false;
	void SetConnection();


protected:
	int ComboBoxIndex = 0;
	const QThread::Priority prior = QThread::TimeCriticalPriority;
	QThread* WorkerThread = new QThread();
	virtual void OpenTab() = 0;
	virtual void CloseTab() = 0;
	TabState ThisState = TabState::start;
	virtual void SetStartState();
	virtual void SetRunningState();
	virtual void SetPausedState();
	virtual void SetEndState();
	virtual void paintEvent(QPaintEvent*)=0;
	void DrawDrawableArea(QPainter*, QPen*, QRect*);

public:
	TabClass(QWidget* parent, int index);
	~TabClass();

	unsigned int Delay = 0;
	TabUI* ThisTab = nullptr;
	QString Name;	
	QWidget* ParentPTR;	//may not be nessecary
};

