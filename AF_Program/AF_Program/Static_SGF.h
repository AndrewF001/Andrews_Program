#pragma once
#include <QtCore>
#include <QtGui>

typedef void (*FPTR)(QPainter*, QPen*, QBrush*, QRect*, std::vector<unsigned int>*);

class Static_SGF
{
public:
	static void GraphicsMethod1(QPainter* Painter, QPen* Pen, QBrush* Brush, QRect* Area,std::vector<unsigned int>* SerilizedData)
	{
		if (SerilizedData->size() == 0)
			return;

		QRect KeyRect;
		int Start_X = Area->x() + 5;
		int Start_Y = Area->y() + Area->height() - 5;
		int ArrSize = SerilizedData->size() - 2;

		double Xspacing = 1;
		int width = std::floor((Area->width() - 10) / (ArrSize));
		double height_mult = ((double)(Area->height() - 10) / (double)(ArrSize));
		if (width == 0)
		{
			width = 1;
			Xspacing = (Area->width() - 10) / (ArrSize + 2);
		}

		for (int i = 0; i < ArrSize; i++)
		{
			if (i == (int)SerilizedData->at(0) || i == (int)SerilizedData->at(1))
			{
				Pen->setColor(Qt::red);
				Brush->setColor(Qt::red);
			}
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
			KeyRect = QRect(Start_X + i * width, Start_Y, width, -(SerilizedData->at(i+2) * height_mult));
			Painter->drawRect(KeyRect);
			Pen->setColor(Qt::black);
			Brush->setColor(Qt::blue);
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
		}

	}

};