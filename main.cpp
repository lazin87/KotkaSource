#include "mainwindow.h"
#include <QApplication>

#include "cprojectsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CProjectsModel oProjectsModel(0);
    w.setModel(&oProjectsModel);
    w.show();

    return a.exec();
}
