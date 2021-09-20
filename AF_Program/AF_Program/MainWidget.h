#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "BaseClasses.h"
#include "TabClass.h"
#include <qtoolbar.h>

/*
    This is the main GUI class that holds all the GUI elements and sets up the inital connections. No work is done here at all
*/

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);
    ~MainWidget();

protected:
    void closeEvent(QCloseEvent*) override;        //need to close up any lose GUI objects that can be created by child objects

private:
    std::vector<TabClass*> Tabs;    //children
    Ui::MainWidgetClass ui;         //home page and QTabWidget
    QToolBar* TB;

    void SetUpToolBar();    //GUI stuff
    void SetUpConnection();
    void SetUpTabs();
};
