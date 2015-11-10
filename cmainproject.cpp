#include "cmainproject.h"

#include "csubproject.h"

CMainProject::CMainProject(QString a_strName)
    : IProject(a_strName)
{

}

CMainProject::~CMainProject()
{

}

bool CMainProject::newSubproject(QString a_strName)
{
    bool fResult = false;

    if( "" != a_strName)
    {
        qDebug("Add new subproject: %s", a_strName.toLatin1().data() );
        m_SubprojectsPtrList.append(new CSubProject(a_strName, this) );
        fResult = true;
    }
    else
    {
        qWarning("CMainProject::newSubproject(): invalid name");
    }

    return fResult;
}

bool CMainProject::removeSubproject(int a_iIndex)
{
    bool fResult = false;

    return fResult;
}



bool CMainProject::addChild(IProject *a_pChild)
{
}

IProject *CMainProject::peekChild(int a_iIndex)
{
}

bool CMainProject::removeChild(int a_iIndex)
{
}
