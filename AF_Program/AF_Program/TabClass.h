#pragma once
#ifndef TABCLASS_H
#define TABCLASS_H
#include "TabUI.h"
#include <qwidget.h>
#include "QtCore"
#include "QtGui"
#include "RunStateEnum.h"

//#include "TabTemplateClass.h"
class TabTemplateClass;

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class TabClass : public QWidget
{
	Q_OBJECT
public slots:
	void PrimaryBtnClicked();
	void SecondaryBtnClicked();
	void AlgoComboBoxChanged(int);
	void Finished();
	void DelaySpinBox(int); 
	void TabChanged(int);

signals:
	void Start();
	void Stop();
	void Restart();
	void Cancle();

private: 
	int index;
	bool Active = false;
	//std::vector<TabTemplateClass*> Algorithms;
	void SetConnection();
	TabTemplateClass* CurrentAlgorithm;
	std::vector<TabTemplateClass*> Algorithms;


protected:
	int ComboBoxIndex = 0;
	int CurrentIndex = 0;
	const QThread::Priority prior = QThread::TimeCriticalPriority;
	QThread WorkerThread;
	TabState ThisState = TabState::start;
	//TabTemplateClass* CurrentAlgorithm;
	//std::vector<TabTemplateClass*> Algorithms;
	virtual void OpenTab() = 0;
	virtual void CloseTab() = 0;

	template<typename T_BaseClass>
	void AddAlgorithm(T_BaseClass AddedClass)
	{
		Algorithms.push_back(AddedClass);
	};
	int NumOfAlgorithms()
	{
		return Algorithms.size();
	}
	template<typename T_BaseClass>
	T_BaseClass FetchCurrentAlgorithm()
	{
		return (T_BaseClass)CurrentAlgorithm;
	}

	virtual void SetStartState();
	virtual void SetRunningState();
	virtual void SetPausedState();
	virtual void SetEndState();
	virtual void CustomDisconnect(TabTemplateClass*)=0;
	virtual void CustomConnect(TabTemplateClass*)=0;
	void CallAfterConstructor();
	void ChangeThreadObj(int);
	void paintEvent(QPaintEvent*);
	virtual void CustomPaintEvent(QPainter*, QPen*, QBrush*,QRect*) = 0;
	void DrawDrawableArea(QPainter*, QPen*, QRect*);

public:
	TabClass(QWidget* parent, int index);
	~TabClass();

	unsigned int Delay = 0;
	TabUI* ThisTab = nullptr;
	QString Name;	
	bool InPaintEvent = false;
	QWidget* ParentPTR;	//may not be nessecary
};

#endif