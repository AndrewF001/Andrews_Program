#pragma once

#include <QWidget>
#include "ui_SortingLeftTitleUi.h"

class SortingLeftTitleUi : public QWidget
{
	Q_OBJECT

public:
	SortingLeftTitleUi(QWidget *parent = Q_NULLPTR);
	~SortingLeftTitleUi();
	Ui::SortingLeftTitleUi ui;
};
