#include "ctask.h"

CTask::CTask(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
{

}

CTask::~CTask()
{

}

bool CTask::isLeaf() const
{
    return true;
}
