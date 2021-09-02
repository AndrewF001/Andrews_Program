#pragma once
#include "TabClass.h"
#include "SortingLeftTitleUi.h"
#include "SortingRightTitleUi.h"
#include "SortingTemplateClass.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "ShellSort.h"
#include "Static_SGF.h"
/*
	extends TabClass so that it can communicate sorting related specific singal/slot with SortingTemplateClass
*/
class SortingBaseClass : public TabClass
{
	Q_OBJECT
	
public slots:
	void SizeSpinboxChanged(int);
	void ShuffleBtnClicked();		
	void ArrayRender(QVariant arr, QVariant ptr);
	void StatRender(long long Timer, int Comparison, int Swaps);

signals:
	void shuffle(int);

public:
	SortingBaseClass(QWidget*, int);
	~SortingBaseClass();

protected:
	void CustomPaintEvent(QPainter*, QPen*, QBrush*,QRect*);

private:	
	int Size = 30;	//Array size
	std::vector<unsigned int> CopyArr;	//Copy array as the array in the worker class will change while GUI class in printing
	FPTR Stored_GFPTR = nullptr;	//Function pointer, used for the algorithm specific painting
	SortingLeftTitleUi* LeftWidget;	//UI
	SortingRightTitleUi* RightWidget;	//UI
	//algorithm classes on heap
	BubbleSort* Bubble;
	MergeSort* Merge;
	ShellSort* Shell;

	void AddAlgorithms();	//could be made virtual in TabClass but left it down to the programmer to deside if they want it
	void OpenTab();			//Redundent, really should remove
	void CloseTab();		//Redundent, really should remove
	void CustomDisconnect(TabTemplateClass*);	//specific QT signal connections
	void CustomConnect(TabTemplateClass*);
	void SetStartState();	//state methods
	void SetRunningState();
	void SetPausedState();
	void SetEndState();
};

