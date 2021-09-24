#include "DebuggerClass.h"

DebuggerClass::DebuggerClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	for (int i = 0; i < NumOfCharts; i++)
	{
		DataArr[i] = nullptr;
	}

	GraphicChart[0] = ui.graphicsView;
	GraphicChart[1] = ui.graphicsView_2;
	GraphicChart[2] = ui.graphicsView_3;
}

DebuggerClass::~DebuggerClass()
{
}

void DebuggerClass::UpdateCharts(QVariant Data)
{
	qDebug() << "In Slot for debug";
	std::vector<DebugPackage> vec = Data.value<std::vector<DebugPackage>>();
	for (int i = 0; i < NumOfCharts; i++)
	{
		if (vec[i].type != D_PackageType::null) {
			QChart* NewChart = vec[i].DecypheredChart();
			SetChartView(i, NewChart);
		}
	}
	qDebug() << "out Slot for debug";
}

void DebuggerClass::SetChartView(int GraphIndex, QChart* Data)
{
	if (!(GraphIndex < NumOfCharts && GraphIndex>-1))
		return;

	GraphicChart[GraphIndex]->setChart(Data);
	delete DataArr[GraphIndex];
	DataArr[GraphIndex] = Data;
}
