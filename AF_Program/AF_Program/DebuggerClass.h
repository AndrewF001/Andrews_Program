#pragma once

#include <QWidget>
#include "ui_DebuggerClass.h"
#include <qlineseries.h>
#include <qareaseries.h>
#include "DebugPackage.h"

class DebuggerClass : public QWidget
{
	Q_OBJECT

public:
	const int NumOfCharts;
	DebuggerClass(QWidget* parent = Q_NULLPTR,const int Num = 3);
	~DebuggerClass();

public slots:
	void UpdateCharts(QVariant);


private:
	Ui::DebuggerClass ui;
	QChart** DataArr;
	QChartView** GraphicChartArr;
	void SetChartView(int, QChart* Data);
};
