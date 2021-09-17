#pragma once
#include <QtCore>
#include <QtGui>

typedef void (*FPTR)(QPainter*, QPen*, QBrush*, QRect*, std::vector<unsigned int>*); //custom function pointer

class Static_SGF
{	//data that is required for the graphics to work
	struct KeyDataStruct 
	{
		int ArrSize;
		int Start_X;
		int Start_Y;
		double XSpacing;
		int width;
		double height_mult;
	};

public:
	//deserizlise the data that's been sent and other variables required
	static KeyDataStruct ProcessValues(QRect* Area, std::vector<unsigned int>* SerilizedData, int offset)
	{
		KeyDataStruct output;

		const static int minWidth = 500;
		const static int minHeight = 300;
		if (Area->width() < minWidth)
			Area->setWidth(minWidth);
		if (Area->height() < minHeight)
			Area->setHeight(minHeight);

		output.ArrSize = SerilizedData->size() - 2 -offset; //offset is the number of non-standard inputs in the serilized data

		output.Start_X = Area->x() + 5;	//gui positioning
		output.Start_Y = Area->y() + Area->height() - 5;

		output.XSpacing = 1;	//work in progress
		output.width = std::floor((Area->width() - 10) / (output.ArrSize));
		output.height_mult = ((double)(Area->height() - 10) / (double)(output.ArrSize));
		if (output.width == 0)
		{
			output.width = 1;
			output.XSpacing = (Area->width() - 10) / (output.ArrSize + 2);
		}
		return output;
	}
	//default visual, need to redesign these methods so they're neater, smarter and faster
	static void GraphicsMethod1(QPainter* Painter, QPen* Pen, QBrush* Brush, QRect* Area,std::vector<unsigned int>* SerilizedData)
	{
		if (SerilizedData->size() == 0)
			return;

		QRect KeyRect;
		KeyDataStruct KeyData = ProcessValues(Area, SerilizedData,0);

		for (int i = 0; i < KeyData.ArrSize; i++)
		{
			if (i == (int)SerilizedData->at(0) || i == (int)SerilizedData->at(1))
			{
				Pen->setColor(Qt::red);
				Brush->setColor(Qt::red);
			}
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
			KeyRect = QRect(KeyData.Start_X + i * KeyData.width, KeyData.Start_Y, KeyData.width, -(SerilizedData->at(i+2) * KeyData.height_mult));
			Painter->drawRect(KeyRect);
			Pen->setColor(Qt::black);
			Brush->setColor(Qt::blue);
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
		}
	}
	//merge sort
	static void GraphicsMethod2(QPainter* Painter, QPen* Pen, QBrush* Brush, QRect* Area, std::vector<unsigned int>* SerilizedData)
	{
		if (SerilizedData->size() == 0)
			return;

		QRect KeyRect;
		KeyDataStruct KeyData = ProcessValues(Area, SerilizedData,2);

		for (int i = 0; i < KeyData.ArrSize; i++)
		{
			if (i == (int)SerilizedData->at(2) || i == (int)SerilizedData->at(3))
			{
				Pen->setColor(Qt::yellow);
				Brush->setColor(Qt::yellow);
			}
			if (i == (int)SerilizedData->at(0) || i == (int)SerilizedData->at(1))
			{
				Pen->setColor(Qt::red);
				Brush->setColor(Qt::red);
			}
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
			KeyRect = QRect(KeyData.Start_X + i * KeyData.width, KeyData.Start_Y, KeyData.width, -(SerilizedData->at(i + 4) * KeyData.height_mult));
			Painter->drawRect(KeyRect);
			Pen->setColor(Qt::black);
			Brush->setColor(Qt::blue);
			Painter->setPen(*Pen);
			Painter->setBrush(*Brush);
		}
	}

};