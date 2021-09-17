#pragma once

#include <QWidget>
#include "ui_CanvasWidget.h"
#include <QtCore>
#include <QtGui>

class TabClass;


class CanvasWidget : public QWidget
{
	Q_OBJECT

public:
	CanvasWidget(TabClass *parent);
	~CanvasWidget();
	TabClass* Parent;
	bool InPaintEvent=false;
	void DrawDrawableArea(QPainter*, QPen*,QRect*);
	void paintEvent(QPaintEvent*) override;


private:
	Ui::CanvasWidget ui;
};
