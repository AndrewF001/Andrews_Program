#pragma once
#include "TabClass.h"
#include "Menu1UI.h"

class TabTemplateClass;

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class Menu1 : public TabClass
{
	Q_OBJECT
public slots:
	void PrimaryBtnClicked();
	void SecondaryBtnClicked();
	void AlgoComboBoxChanged(int);
	void DelaySpinBox(int);


public:
	Menu1(QWidget* parent, int index);
	~Menu1();

	Menu1UI* MenuObject = new Menu1UI(this);
	unsigned int Delay = 5;	//public as it allows worker thread to read it(shouldn't change the value)

protected:
	int ComboBoxIndex = 0;	//algorithm index

	virtual void OpenTab() = 0;		//redundent at the moment
	virtual void CloseTab() = 0;	//redundent at the moment
	virtual void SetStartState();	//state change methods
	virtual void SetRunningState();
	virtual void SetPausedState();
	virtual void SetEndState();
	virtual void CustomDisconnect(TabTemplateClass*) = 0;	//Child class specific QT signals to be disconnected
	virtual void CustomConnect(TabTemplateClass*) = 0;	//Child class specific QT signals to be connected
														//signals should match in both class
	virtual void CustomPaintEvent(QPainter*, QPen*, QBrush*, QRect*) = 0;	//specific tab draw event

private:
	void SetConnection();
	void C_CACB();
	void C_CACL(int i);

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

