#pragma once

#include <QWidget>
#include <QtGui>
#include <qtextedit.h>
#include "ui_TextWidget.h"

/*
	Class for the text files that open when you request to see the code of the algorithm,
	works completely independent from the worker class(only associated by name)
*/

class TextWidget : public QWidget
{
	Q_OBJECT

public:
	TextWidget(std::vector<std::string>*);
	~TextWidget();

public slots:
	void Delete();

private:
	QTextEdit* Editor;
	Ui::TextWidget ui;

	QString QStringConversion(std::vector<std::string>*);

};
