#include "mainwindow.h"

#include <QStyleFactory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
#include <QStyleFactory>

    MainWindow w;
    w.show();
    return a.exec();
}
