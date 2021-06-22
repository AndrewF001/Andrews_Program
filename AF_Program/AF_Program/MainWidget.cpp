#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //setting up a tool bar for the main ui
    TB = new QToolBar(this);
    TB->setAutoFillBackground(true);
    TB->addAction("Test");
    ui.gridLayout->setMenuBar(TB);
}
