#pragma once
#include "TabUI.h"
#include "CanvasWidget.h"
#include "DebuggerClass.h"
#include <qwidget.h>
#include "QtCore"
#include "QtGui"
#include "RunStateEnum.h"
#include "TextWidget.h"
#include <qmessagebox.h>
#include <fstream>
#include <QtCharts>

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
	void DebugCheckChanged(int state);
		

signals:
	void Start();
	void Restart();
	void Cancle();
	void Stop();
	void CloseTextFiles();

public:
	TabClass(QWidget* parent, const bool Debug);
	~TabClass();

	TabUI* ThisTab = nullptr;
	QString Name;
	QWidget* ParentPTR;	//may not be nessecary
	CanvasWidget* Canvas;
	DebuggerClass* Debugger;

	void WindowClosed() { emit CloseTextFiles(); };
	void SetIndex(int i) { CurrentIndex = i; };

	virtual void CustomPaintEvent(QPainter*, QPen*, QBrush*, QRect*) = 0;	//specific tab draw event


protected:
	int CurrentIndex = 0;	//Tab index
	std::string FileHeader = "Def_";	//header for text file
	const static QThread::Priority prior = QThread::TimeCriticalPriority;	//setting for thread(for the time being every tab has the same priority)
	QThread WorkerThread;	//each tab gets there own Thread and only one.
	TabState ThisState = TabState::start;	//not really used
	const bool Debug_Option = false;	//if debug is an option
	bool Debug_Active = false;	//debug var

	void CallAfterConstructor();	//Couldn't work out how to run repeated code after child constructor was finished
	void ChangeThreadObj(int);		//switches signal and slot for algrothim
	virtual void OpenTab() = 0;		//redundent at the moment
	virtual void CloseTab() = 0;	//redundent at the moment
	virtual void SetStartState();	//state change methods
	virtual void SetRunningState();
	virtual void SetPausedState();
	virtual void SetEndState();
	virtual void CustomDisconnect(TabTemplateClass*)=0;	//Child class specific QT signals to be disconnected
	virtual void CustomConnect(TabTemplateClass*)=0;	//Child class specific QT signals to be connected
														//signals should match in both class

	int index;	//redundent at the moment and need to edit constructor so it isn't set then but in the for loop
	bool Active = false;
	TabTemplateClass* CurrentAlgorithm;	//ease of use
	std::vector<TabTemplateClass*> Algorithms;	//add algroithm
	std::vector<TextWidget*> FileVect;	//memory leak for each pointer created but actual object is deleted
	
	virtual void SetConnection() {};
	virtual void C_CACB() {};	//child call after constructor before method
	virtual void C_CACL(int i) {};	//child call after constructor loop method

private:
	QList<int> Sizes;
	void DebugConstructor();
	void DebugOn();
	void DebugOff();
	void paintEvent(QPaintEvent*) override { Canvas->update(); }; //update canvas paint event when widget is called for

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