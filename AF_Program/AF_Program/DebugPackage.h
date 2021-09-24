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
	std::vector<QBarSet*> BarData;
	QLineSeries* AreaData[2] = { nullptr,nullptr };
	DebugPackage();
	~DebugPackage();
	QChart* DecypheredChart();

private:
	
	QChart* CreateAreaChart();
	QChart* CreateBarChart();

};

