#include "ctask.h"

CTask::CTask(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
    , m_oStandardItem(a_strName)
{

}

CTask::~CTask()
{

}



bool CTask::isLeaf() const
{
    return true;
}


bool CTask::addChild(IProject *a_pChild)
{
    Q_UNUSED(a_pChild)

    return false;
}

IProject *CTask::peekChild(int a_iIndex)
{
    Q_UNUSED(a_iIndex)

    return 0;
}

bool CTask::removeChild(int a_iIndex)
{
    Q_UNUSED(a_iIndex)

    return false;
}


void CTask::removeAllChildren()
{
    // intentionaly empty
}


QStandardItem *CTask::getStandardItem()
{
    return & m_oStandardItem;
}
