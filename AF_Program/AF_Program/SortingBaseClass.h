#pragma once
#include "TabClass.h"
#include "SortingLeftTitleUi.h"
#include "SortingRightTitleUi.h"
#include "SortingTemplateClass.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "ShellSort.h"
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
	void AlgoComboBoxChanged(int);
	void SizeSpinboxChanged(int);
	void ShuffleBtnClicked();
	void ArrayRender(QVariant arr, int index1, int index2);
	void StatRender(long long Timer, int Comparison, int Swaps);

signals:
	void shuffle(int);

protected:
	void CustomPaintEvent(QPainter*, QPen*, QBrush*,QRect*);

private:
	int Size = 30;
	int CurrentIndex = 0;
	std::vector<unsigned int> CopyArr;
	int Index1=0, Index2=1;
	SortingLeftTitleUi* LeftWidget;
	SortingRightTitleUi* RightWidget;

	BubbleSort* Bubble;
	MergeSort* Merge;
	ShellSort* Shell;

	//SortingTemplateClass* CurrentAlgorithm;
	//std::vector<SortingTemplateClass*> Algorithms;
	void AddAlgorithms();
	void ChangeThreadObj(int);
	void OpenTab();
	void CloseTab();
	void SetStartState();
	void SetRunningState();
	void SetPausedState();
	void SetEndState();
	void DrawArrayUI(QPainter* , QPen*,QBrush* , QRect*);

};

