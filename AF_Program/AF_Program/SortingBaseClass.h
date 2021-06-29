#pragma once
#include "TabClass.h"
#include "SortingLeftTitleUi.h"
#include "SortingRightTitleUi.h"
#include "SortingTemplateClass.h"
#include "qwidget.h"
#include "QtCore"
#include "QtGui"

/*
	extends TabClass so that it can communicate sorting related specific singal/slot with SortingTemplateClass
*/
class SortingBaseClass : public TabClass
{
	Q_OBJECT

public:
	SortingBaseClass(QWidget *);
	virtual ~SortingBaseClass();
	
public slots:
	void PrimaryBtnClicked();
	void SecondaryBtnClicked();
	void AlgoComboBoxChanged(int);
	void SizeSpinboxChanged(int);
	void ShuffleBtnClicked();

private:
	int Size = 30;
	SortingLeftTitleUi* LeftWidget;
	SortingRightTitleUi* RightWidget;
	std::vector<SortingTemplateClass*> Algorithms;

};

