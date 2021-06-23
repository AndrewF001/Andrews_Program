#pragma once

#include <QWidget>
#include "ui_TabTemplate.h"

class TabTemplate : public QWidget
{
	Q_OBJECT

public:
	TabTemplate(QWidget *parent = Q_NULLPTR);
	~TabTemplate();
	Ui::TabTemplate ui;
};
