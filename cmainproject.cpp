#include "cmainproject.h"

#include <QDebug>

CMainProject::CMainProject(QString a_strName)
    : CProjectBase(a_strName)
{

}

CMainProject::~CMainProject()
{
    qDebug() << "CMainProject::~CMainProject()";
    removeAllChildren();
}

bool CMainProject::newSubproject(QString a_strName)
{
    bool fResult = false;



    return fResult;
}

bool CMainProject::removeSubproject(int a_iIndex)
{
    bool fResult = false;

    return fResult;
}
