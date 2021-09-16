#pragma once

#include <QWidget>
#include "ui_Menu1Bar.h"

/*
	Like MainWidget class this is the UI elements that each tab will use as it's base.
	up to programmer if they want to inherit this class or insert a new UI class into the provided widgets for this base class.
*/

class Menu1UI : public QWidget
{
	Q_OBJECT

public:
	Menu1UI(QWidget* parent = Q_NULLPTR);
	~Menu1UI();

	Ui::MenuBar1 ui;
};

