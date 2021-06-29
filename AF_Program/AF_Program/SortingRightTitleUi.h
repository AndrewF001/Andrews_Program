#pragma once

#include <QWidget>
#include "ui_SortingRightTitleUi.h"

class SortingRightTitleUi : public QWidget
{
	Q_OBJECT

public:
	SortingRightTitleUi(QWidget *parent = Q_NULLPTR);
	~SortingRightTitleUi();
	Ui::SortingRightTitleUi ui;
};
