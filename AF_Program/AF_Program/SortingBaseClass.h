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

public:
	SortingBaseClass(QWidget *, int);
	virtual ~SortingBaseClass();
	
public slots:
	void SizeSpinboxChanged(int);
	void ShuffleBtnClicked();
	void ArrayRender(QVariant arr, QVariant ptr);
	void StatRender(long long Timer, int Comparison, int Swaps);

signals:
	void shuffle(int);

protected:
	void CustomPaintEvent(QPainter*, QPen*, QBrush*,QRect*);

private:
	int Size = 30;
	std::vector<unsigned int> CopyArr;
	FPTR Stored_GFPTR = nullptr;
	SortingLeftTitleUi* LeftWidget;
	SortingRightTitleUi* RightWidget;

	BubbleSort* Bubble;
	MergeSort* Merge;
	ShellSort* Shell;

	void AddAlgorithms();
	void OpenTab();
	void CloseTab();
	void CustomDisconnect(TabTemplateClass*);
	void CustomConnect(TabTemplateClass*);
	void SetStartState();
	void SetRunningState();
	void SetPausedState();
	void SetEndState();
	void DrawArrayUI(QPainter* , QPen*,QBrush* , QRect*);

};

