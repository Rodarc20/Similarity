#include "buscador.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Buscador w;
    w.show();

    return a.exec();
}
