#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "BaseClasses.h"
#include "TabClass.h"
#include <qtoolbar.h>

/*
    This is the main class that holds all the GUI elements and sets up the inital connections. No work is done here at all
*/

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

private:
    void SetUpToolBar();
    void SetUpConnection();
    void SetUpTabs();

    std::vector<TabClass*> Tabs;
    Ui::MainWidgetClass ui;
    QToolBar* TB;
};
