#include "DebugPackage.h"

DebugPackage::DebugPackage()
{

}

DebugPackage::~DebugPackage()
{

}

QChart* DebugPackage::DecypheredChart()
{
	switch (type)
	{
	case(null):
		return nullptr;
	case(BarChart):
		break;
	case(AreaChart):
		
	}
	return nullptr;
}

QChart* DebugPackage::CreateAreaChart(QLineSeries* Series1, QLineSeries* Series2)
{
	QAreaSeries* AreaSeries = new QAreaSeries(Series1, Series2);

	QPen pen(0x059605);
	pen.setWidth(3);
	AreaSeries->setPen(pen);

	QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
	gradient.setColorAt(0.0, 0x3cc63c);
	gradient.setColorAt(1.0, 0x26f626);
	gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
	AreaSeries->setBrush(gradient);

	int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;

	QVector<QPointF> points = Series1->pointsVector();
	if (Series2 != nullptr)
		points += Series2->pointsVector();

	for (int i = 0; i < points.count(); i++)
	{
		if (points[i].y() > maxy)
			maxy = points[i].y();

		if (points[i].x() > maxx)
			maxx = points[i].x();
		if (points[i].x() < minx)
			minx = points[i].x();
	}

	QChart* Chart = new QChart();
	Chart->addSeries(AreaSeries);
	Chart->createDefaultAxes();
	Chart->axes(Qt::Horizontal).first()->setRange(minx, maxx);
	Chart->axes(Qt::Vertical).first()->setRange(0, (int)(maxy * 1.1));

	return Chart;
}