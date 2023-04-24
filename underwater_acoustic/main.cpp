#include "underwater_acoustic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    underwater_acoustic w;

    w.setFixedSize(1280, 650);
    w.show();
    return a.exec();
}
