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
    Tabs.push_back(new SortingBaseClass(this,1));
    for (int i = 0; i < Tabs.size(); i++)
    {
        ui.tabWidget->addTab(Tabs[i]->ThisTab, Tabs[i]->Name);
        connect(ui.tabWidget, &QTabWidget::tabBarClicked, Tabs[i], &TabClass::TabChanged);
    }
}