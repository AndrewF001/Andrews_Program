#pragma once
#include "TabUI.h"
#include <qwidget.h>
#include "QtCore"
#include "QtGui"

/*
This is the class that connects the MainWidget and worker threads together.
It stores the nesscessary variables that are required by every tab and stores the UI so that mainwidget can store a vector of them
*/

class TabClass : public QObject
{
	Q_OBJECT
public slots:
	virtual void PrimaryBtnClicked() = 0;
	virtual void SecondaryBtnClicked() = 0;
	virtual void AlgoComboBoxChanged(int) = 0;
	void DelaySpinBox(int);

private: 
	void SetConnection();

protected:
	int ComboBoxIndex;
	unsigned int Delay;

public:
	TabClass(QWidget*);
	~TabClass();

	TabUI* ThisTab = nullptr;
	QString Name;	
	QWidget* ParentPTR;	//may not be nessecary
};

