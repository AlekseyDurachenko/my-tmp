#include "mainwindow.h"
#include <QApplication>
#include "cbookmark.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    qRegisterMetaType<CBookmark>("CBookmark");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
