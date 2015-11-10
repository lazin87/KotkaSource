#include "csubproject.h"

CSubProject::CSubProject(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
{

}

CSubProject::~CSubProject()
{

}



bool CSubProject::addChild(IProject *a_pChild)
{
}

IProject *CSubProject::peekChild(int a_iIndex)
{
}

bool CSubProject::removeChild(int a_iIndex)
{
}