#pragma once
#include <qvariant.h>
#include <QtCharts>
enum D_PackageType
{
	null,
	BarChart,
	AreaChart
};

class DebugPackage
{

public:
	D_PackageType type = D_PackageType::null;
	QString Title, Y_Title, X_Title;
	QVariant Data = null;
	DebugPackage();
	~DebugPackage();
	QChart* DecypheredChart();

private:
	QChart* CreateAreaChart(QLineSeries*, QLineSeries* = nullptr);
	//QChart* CreateBarChart(QLineSeries*, QLineSeries* = nullptr);

};

