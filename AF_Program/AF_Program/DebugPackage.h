#pragma once
#include <qvariant.h>
#include <QtCharts>

typedef QChart* (*D_FPTR)(std::vector<unsigned char>*, QList<QAbstractSeries*>*);

enum D_PackageType
{
	null,
	Basic_BarChart,
	Basic_AreaChart,
	CustomChart
};

class DebugPackage
{

public:
	D_PackageType type = D_PackageType::null;
	std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
	QString Title, Y_Title, X_Title;
	std::vector<unsigned char> Data;
	DebugPackage();
	~DebugPackage();
	QChart* DecypheredChart(QList<QAbstractSeries*>*);

private:
	
	QChart* CreateAreaChart();
	QChart* CreateBarChart();

};

