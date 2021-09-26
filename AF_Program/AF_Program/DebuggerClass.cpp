#include "DebuggerClass.h"

DebuggerClass::DebuggerClass(QWidget* parent, const int x)
	: QWidget(parent), NumOfCharts(x)
{
	ui.setupUi(this);

	DataArr = new QChart* [NumOfCharts];
	GraphicChartArr = new QChartView* [NumOfCharts];
	for (int i = NumOfCharts-1; i > -1; i--)
	{
		GraphicChartArr[i] = new QChartView(this);
		ui.verticalLayout->insertWidget(0, GraphicChartArr[i]);
		DataArr[i] = nullptr;
	}
}

DebuggerClass::~DebuggerClass()
{
}

void DebuggerClass::UpdateCharts(QVariant Data, bool Replace)
{
	qDebug() << "In debug slot";
	std::vector<DebugPackage> vec = Data.value<std::vector<DebugPackage>>();
	for (int i = 0; i < NumOfCharts; i++)
	{
		QList<QAbstractSeries*> CurrentData = QList<QAbstractSeries*>();
		if(!Replace && DataArr[i]!=nullptr)
			CurrentData = DataArr[i]->series();

		if (vec[i].type != D_PackageType::null) {
			QChart* NewChart = vec[i].DecypheredChart(&CurrentData);
			SetChartView(i, NewChart);
		}
	}
	qDebug() << "out debug slot";
}

void DebuggerClass::SetChartView(int GraphIndex, QChart* Data)
{
	if (!(GraphIndex < NumOfCharts && GraphIndex>-1))
		return;

	GraphicChartArr[GraphIndex]->setChart(Data);
	delete DataArr[GraphIndex];
	DataArr[GraphIndex] = Data;
}
