#include <QApplication>
#include <QTime>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QTime time = QTime::currentTime();
    qsrand(static_cast<uint>(time.msec()));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
