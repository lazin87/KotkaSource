#include "mainwindow.h"
#include <QApplication>


// headers to test
#include "cprojectmanager.h"
// end headers to test

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // just to test
    CProjectManager oProjectMngr;
    w.setModel(oProjectMngr.getModel() );

    QObject::connect( &w, SIGNAL(createProject(KotkaSource::SProjectData&,QModelIndex& ) )
                    , &oProjectMngr, SLOT(createProjectSlot(KotkaSource::SProjectData&,QModelIndex&) )
                    );
    // end just to test
    return a.exec();
}
