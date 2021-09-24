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
	const static int NumOfCharts = 3;
	DebuggerClass(QWidget* parent = Q_NULLPTR);
	~DebuggerClass();

public slots:
	void UpdateCharts(QVariant);


private:
	Ui::DebuggerClass ui;
	QChart* DataArr[NumOfCharts];
	QChartView* GraphicChart[NumOfCharts];
	void SetChartView(int, QChart* Data);
};
