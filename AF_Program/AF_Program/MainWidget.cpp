#include "MainWidget.h"


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    SetUpToolBar();
    
    SetUpTabs();

    SetUpConnection();
}

/*
* because I messed up and choose QWidget instead of QMainWindow
*/
void MainWidget::SetUpToolBar()
{
    TB = new QToolBar(this);
    TB->setAutoFillBackground(true);
    TB->addAction("Test");
    ui.gridLayout->setMenuBar(TB);
}

/*
All the nessecary slots and signals are created here
*/
void MainWidget::SetUpConnection()
{

}

/*
This method will create all the tabs for the main UI.
*/
void MainWidget::SetUpTabs()
{
    //Tabs.push_back(new SortingBaseClass());

}