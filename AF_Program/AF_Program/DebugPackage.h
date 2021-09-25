#pragma once
#include <qvariant.h>
#include <QtCharts>

typedef QChart* (*D_FPTR)(std::vector<unsigned int>*);

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
	std::vector<char> Data;
	DebugPackage();
	~DebugPackage();
	QChart* DecypheredChart();

private:
	
	QChart* CreateAreaChart();
	QChart* CreateBarChart();

};

