#include "mainwindow.h"

#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextStream cout(stdout);
    w.show();
    return a.exec();
}
