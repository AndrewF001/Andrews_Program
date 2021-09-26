#include "DebugPackage.h"

DebugPackage::DebugPackage()
{

}

DebugPackage::~DebugPackage()
{

}

QChart* DebugPackage::DecypheredChart(QList<QAbstractSeries*>* CurrentSeries)
{
	switch (type)
	{
	case(null):
		return nullptr;
	case(Basic_BarChart):
		return CreateBarChart(CurrentSeries);
	case(Basic_AreaChart):
		return CreateAreaChart(CurrentSeries);
	case(CustomChart):
		return CustomChartPointer(RawData, CurrentSeries);
	}
	return nullptr;
}

QChart* DebugPackage::CreateAreaChart(QList<QAbstractSeries*>* CurrentSeries)
{
	AreaPackage Data;
	Serilizer::deserialize(Data, RawData);
	for (int i = 0; i < 2; i++)
	{
		if (dynamic_cast<QLineSeries*>(CurrentSeries->at(i)))//maybe work?
		{

		}
	}

	/*QAreaSeries* AreaSeries = new QAreaSeries(AreaData, AreaData[1]);

	QPen pen(0x059605);
	pen.setWidth(3);
	AreaSeries->setPen(pen);

	QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
	gradient.setColorAt(0.0, 0x3cc63c);
	gradient.setColorAt(1.0, 0x26f626);
	gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
	AreaSeries->setBrush(gradient);

	int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;

	QVector<QPointF> points = AreaData[0]->pointsVector();
	if (AreaData[1] != nullptr)
		points += AreaData[1]->pointsVector();

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

	return Chart;*/
	return nullptr;
}

QChart* DebugPackage::CreateBarChart(QList<QAbstractSeries*>* CurrentSeries)
{
	/*QBarSeries* Series = new QBarSeries();
	for (int i = 0; i < BarData.size(); i++)
	{
		Series->append(BarData[i]);
	}

	QChart* Chart = new QChart();
	Chart->addSeries(Series);
	Chart->setTitle("Simple barchart example");
	Chart->setAnimationOptions(QChart::SeriesAnimations);

	return Chart;*/
	return nullptr;
}