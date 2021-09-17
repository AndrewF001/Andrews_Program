#include "CanvasWidget.h"
#include "TabClass.h"

CanvasWidget::CanvasWidget(TabClass *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Parent = parent;
	setAutoFillBackground(true);
	QPalette pal(QPalette::Window, Qt::white);
	setPalette(pal);
}

CanvasWidget::~CanvasWidget()
{
}

void CanvasWidget::paintEvent(QPaintEvent* event)
{
	InPaintEvent = true;
	QPainter paint(this);
	QPen Pen(Qt::black);
	QBrush Brush(Qt::white);

	QRect Rect(QPoint(0,0),Parent->ThisTab->ui.CanvasScrollArea->size());
	Rect.setWidth(Rect.width() - 5);
	Rect.setHeight(Rect.height() - 5);
	
	Parent->CustomPaintEvent(&paint, &Pen, &Brush, &Rect);
	DrawDrawableArea(&paint, &Pen, &Rect);
	setMinimumSize(Rect.size());

	InPaintEvent = false;
}

void CanvasWidget::DrawDrawableArea(QPainter* Painter, QPen* Pen, QRect* Rect)
{
	Pen->setWidth(3);
	Pen->setColor(Qt::black);
	Painter->setPen(*Pen);
	Painter->setBrush(QBrush());
	Painter->drawRect(*Rect);
	Pen->setWidth(1);
}