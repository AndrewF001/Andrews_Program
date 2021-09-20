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
    DO NOT TOUCH THIS DESTRUCTOR!!!
    My first case of weird programming languages ever!!!
    why does the implicitly declared destructor from the constructor that
    is the exact same as bellow not work but when it's explicitly typed it does???
    WTF!!!
    So many hours of debugging! why does this happen!
    Code wise they're both the same???
*/
MainWidget::~MainWidget()
{
 
}

void MainWidget::closeEvent(QCloseEvent* event)
{
    for (int i = 0; i < Tabs.size(); i++)
    {
        Tabs[i]->WindowClosed();
    }
    event->accept();
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
    Tabs.push_back(new SortingBaseClass(this));


    for (int i = 0; i < Tabs.size(); i++)
    {
        Tabs[i]->SetIndex(i);
        ui.tabWidget->addTab(Tabs[i], Tabs[i]->Name);
        ui.tabWidget->widget(i + 1)->setLayout(Tabs[i]->ThisTab->ui.MaingridLayout);
        connect(ui.tabWidget, &QTabWidget::tabBarClicked, Tabs[i], &TabClass::TabChanged);
    }
}