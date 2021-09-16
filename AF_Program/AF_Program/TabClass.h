#pragma once
#include "TabUI.h"
#include <qwidget.h>
#include "QtCore"
#include "QtGui"
#include "RunStateEnum.h"
#include "TextWidget.h"
#include <qmessagebox.h>
#include <fstream>

class TabTemplateClass;

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class TabClass : public QWidget
{
	Q_OBJECT
public slots:
	void Finished();
	void TabChanged(int);
	void TextFileBtnClicked();
		

signals:
	void Start();
	void Restart();
	void Cancle();
	void Stop();
	void CloseTextFiles();

public:
	TabClass(QWidget* parent, int index);
	~TabClass();

	TabUI* ThisTab = nullptr;
	QString Name;
	bool InPaintEvent = false; //efficenty variable
	QWidget* ParentPTR;	//may not be nessecary

	void WindowClosed() { emit CloseTextFiles(); };


protected:
	int CurrentIndex = 0;	//Tab index
	std::string FileHeader = "Def_";	//header for text file
	const static QThread::Priority prior = QThread::TimeCriticalPriority;	//setting for thread(for the time being every tab has the same priority)
	QThread WorkerThread;	//each tab gets there own Thread and only one.
	TabState ThisState = TabState::start;	//not really used

	void CallAfterConstructor();	//Couldn't work out how to run repeated code after child constructor was finished
	void ChangeThreadObj(int);		//switches signal and slot for algrothim
	void paintEvent(QPaintEvent*);	
	void DrawDrawableArea(QPainter*, QPen*, QRect*);
	virtual void OpenTab() = 0;		//redundent at the moment
	virtual void CloseTab() = 0;	//redundent at the moment
	virtual void SetStartState();	//state change methods
	virtual void SetRunningState();
	virtual void SetPausedState();
	virtual void SetEndState();
	virtual void CustomDisconnect(TabTemplateClass*)=0;	//Child class specific QT signals to be disconnected
	virtual void CustomConnect(TabTemplateClass*)=0;	//Child class specific QT signals to be connected
														//signals should match in both class
	virtual void CustomPaintEvent(QPainter*, QPen*, QBrush*,QRect*) = 0;	//specific tab draw event

	int index;	//redundent at the moment and need to edit constructor so it isn't set then but in the for loop
	bool Active = false;
	TabTemplateClass* CurrentAlgorithm;	//ease of use
	std::vector<TabTemplateClass*> Algorithms;	//add algroithm
	std::vector<TextWidget*> FileVect;	//memory leak for each pointer created but actual object is deleted
	
	virtual void SetConnection() {};
	virtual void C_CACB() {};
	virtual void C_CACL(int i) {};

protected:	//work in progress, need to set up dynamic_cast so you can't insert non-valid types into the vector
	template<typename T_BaseClass>
	void AddAlgorithm(T_BaseClass AddedClass)
	{
		Algorithms.push_back(AddedClass);
	};
	int NumOfAlgorithms()
	{
		return (int)Algorithms.size();
	}
	template<typename T_BaseClass>
	T_BaseClass FetchCurrentAlgorithm()
	{
		return (T_BaseClass)CurrentAlgorithm;
	}
};