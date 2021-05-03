#include "mainwindow.h"
#include "image_processor.h"
#include <QResource>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
