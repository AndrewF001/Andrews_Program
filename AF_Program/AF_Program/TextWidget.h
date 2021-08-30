#pragma once

#include <QWidget>
#include <QtGui>
#include <qtextedit.h>
#include "ui_TextWidget.h"


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
