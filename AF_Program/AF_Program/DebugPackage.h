#pragma once
#include <qvariant.h>
#include <QtCharts>
#include "Serilizer.h"

typedef QChart* (*D_FPTR)(unsigned char*, QList<QAbstractSeries*>*);

enum D_PackageType
{
	null,
	Basic_BarChart,
	Basic_AreaChart,
	CustomChart
};

class BarPackage
{
	std::vector<QBarSet*> Sets;
};

class AreaPackage
{
	QPointF NewValue[2];
};

class DebugPackage
{

public:
	D_PackageType type = D_PackageType::null;
	std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
	QString Title, Y_Title, X_Title;
	unsigned char* RawData;
	D_FPTR CustomChartPointer = nullptr;
	DebugPackage();
	~DebugPackage();
	QChart* DecypheredChart(QList<QAbstractSeries*>*);

private:
	
	QChart* CreateAreaChart(QList<QAbstractSeries*>*);
	QChart* CreateBarChart(QList<QAbstractSeries*>*);

};

