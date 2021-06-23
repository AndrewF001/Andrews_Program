#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"
#include "BaseClasses.h"
#include "TabClass.h"
#include <qtoolbar.h>

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
