#pragma once

#include <QWidget>
#include "ui_TabUI.h"

/*
	Like MainWidget class this is the UI elements that each tab will use as it's base.
	up to programmer if they want to inherit this class or insert a new UI class into the provided widgets for this base class.
*/

class TabUI : public QWidget
{
	Q_OBJECT

public:
	TabUI(QWidget *parent = Q_NULLPTR);
	~TabUI();
	Ui::TabUI ui;
};
