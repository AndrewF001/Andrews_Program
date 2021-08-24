#pragma once
#include <QtCore>
#include <QtGui>

typedef void (*FPTR)(QPainter*, QPen*, QBrush*, QRect*, std::vector<unsigned int>*);

static class Static_SGF
{
	static void GraphicsMethod1(QPainter* Painter, QPen* Pen, QBrush* Brush, QRect* Area,std::vector<unsigned int>* SerilizedData)
	{
		/*if (CopyArr.size() == 0)
			return;

		QRect KeyRect;
		int Start_X = Area->x() + 5;
		int Start_Y = Area->y() + Area->height() - 5;

		double Xspacing = 1;
		int width = std::floor((Area->width() - 10) / (CopyArr.size()));
		double height_mult = ((double)(Area->height() - 10) / (double)(CopyArr.size()));
		if (width == 0)
		{
			width = 1;
			Xspacing = (Area->width() - 10) / (CopyArr.size() + 2);
		}

		for (int i = 0; i < CopyArr.size(); i++)
		{
			if (i == Index1 || i == Index2)
			{
				Pen->setColor(Qt::red);
				Brush->setColor(Qt::red);
			}
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
			KeyRect = QRect(Start_X + i * width, Start_Y, width, -(CopyArr[i] * height_mult));
			Painter->drawRect(KeyRect);
			Pen->setColor(Qt::black);
			Brush->setColor(Qt::blue);
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
		}*/

	}

};