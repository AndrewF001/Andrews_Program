#pragma once

#include <QWidget>
#include "ui_DebuggerClass.h"

class DebuggerClass : public QWidget
{
	Q_OBJECT

public:
	DebuggerClass(QWidget *parent = Q_NULLPTR);
	~DebuggerClass();

private:
	Ui::DebuggerClass ui;
};