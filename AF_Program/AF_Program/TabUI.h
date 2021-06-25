#pragma once

#include <QWidget>
#include "ui_TabUI.h"

class TabUI : public QWidget
{
	Q_OBJECT

public:
	TabUI(QWidget *parent = Q_NULLPTR);
	~TabUI();
	Ui::TabUI ui;
};
