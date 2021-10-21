#include "MainWidget.h"
#include <QtWidgets/QApplication>

#include "Serilizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
