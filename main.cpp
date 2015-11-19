#include "mainwindow.h"
#include <QApplication>


// headers to test
#include "cprojectsmodel.h"
#include "cprojectmanager.h"
// end headers to test
void TC_fillInProjectTreeView(MainWindow & a_rWindow, CProjectManager & a_rProjectMngr);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // just to test
    CProjectManager oProjectMngr;
    w.setModel(oProjectMngr.getModel() );

    QObject::connect( &w, SIGNAL(createNewProject(KotkaSource::SProjectData& ) )
                    , &oProjectMngr, SLOT(createProjectSlot(KotkaSource::SProjectData& ) )
                    );
    QObject::connect( &w, SIGNAL(createSubproject(KotkaSource::SProjectData&,QModelIndex& ) )
                    , &oProjectMngr, SLOT(createProjectSlot(KotkaSource::SProjectData&,QModelIndex&) )
                    );

    //TC_fillInProjectTreeView(w, oProjectMngr);
    // end just to test
    return a.exec();
}
