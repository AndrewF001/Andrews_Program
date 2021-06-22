#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include <QtCore>
#include <QtGUI>
#include <qtoolbar.h>
#include <qstyle.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWidgetClass ui;
    QToolBar* TB;
};
