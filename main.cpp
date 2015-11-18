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
    oProjectMngr.createProject("MainProject1");
    w.updateModel(oProjectMngr.getModel() );
    QObject::connect( &oProjectMngr, SIGNAL(projectModelWasChanged(QAbstractItemModel* ) )
                     , &w, SLOT(updateModel(QAbstractItemModel* ) )
                     );
    //TC_fillInProjectTreeView(w, oProjectMngr);
    // end just to test
    return a.exec();
}

void TC_fillInProjectTreeView(MainWindow & a_rWindow, CProjectManager &a_rProjectMngr)
{
    // just to test

    a_rProjectMngr.createProject("MainProject1");
    a_rProjectMngr.createProject("MainProject2");
    a_rProjectMngr.createProject("MainProject3");
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(0), "SubProject1" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(0), "SubProject2" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(0), "SubProject3" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(0), "Task1" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(0), "Task2" );

    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(1), "SubProject1" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(1), "Task1" );

    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(2), "SubProject1" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(2), "SubProject2" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(2), "SubProject3" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(2), "SubProject4" );
    a_rProjectMngr.createSubproject(*a_rProjectMngr.getProject(2), "SubProject5" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(2), "Task1" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(2), "Task2" );
    a_rProjectMngr.createTask(*a_rProjectMngr.getProject(2), "Task3" );

    a_rWindow.updateModel(a_rProjectMngr.getModel() );
}
