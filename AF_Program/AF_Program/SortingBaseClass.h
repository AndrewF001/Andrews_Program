#pragma once
#include "TabClass.h"
#include "SortingLeftTitleUi.h"
#include "SortingRightTitleUi.h"
#include "SortingTemplateClass.h"
#include "qwidget.h"
#include "QtCore"
#include "QtGui"
#include "BubbleSort.h"

/*
	extends TabClass so that it can communicate sorting related specific singal/slot with SortingTemplateClass
*/
class SortingBaseClass : public TabClass
{
	Q_OBJECT

public:
	SortingBaseClass(QWidget *, int);
	virtual ~SortingBaseClass();
	
public slots:
	void PrimaryBtnClicked();
	void SecondaryBtnClicked();
	void AlgoComboBoxChanged(int);
	void Finished();
	void SizeSpinboxChanged(int);
	void ShuffleBtnClicked();
	void ArrayRender(std::vector<unsigned int> arr, int index1, int index2);
	void StatRender(long long, int, int); 

signals:
	void shuffle(int);

private:
	int Size = 30;
	int CurrentIndex = 0;
	SortingLeftTitleUi* LeftWidget;
	SortingRightTitleUi* RightWidget;
	BubbleSort* Bubble;
	SortingTemplateClass* CurrentAlgorithm;
	std::vector<SortingTemplateClass*> Algorithms;
	void AddAlgorithms();
	bool ChangeThreadObj(int);
	void OpenTab();
	void CloseTab();
	void SetStartState();
	void SetRunningState();
	void SetPausedState();
	void SetEndState();

};

