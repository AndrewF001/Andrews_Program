#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include "Serilizer.h"

class test {
public:
    int x;
};

int main(int argc, char *argv[])
{
    test* Original = new test();
    Original->x = 1;
    unsigned char* buffer = Serilizer::Safe_Serialize(Original);
    test* copy = Serilizer::Safe_Deserialize<test>(buffer);
    int y = copy->x;

    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
