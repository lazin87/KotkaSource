#include "ctask.h"

CTask::CTask(QString a_strName, const CProject * a_pProjectParent)
    : CProject(a_strName, a_pProjectParent)
{

}

CTask::~CTask()
{

}



bool CTask::isLeaf() const
{
    return true;
}
