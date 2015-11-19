#include "ctask.h"

CTask::CTask(QString a_strName)
    : IProject(a_strName)
{

}

CTask::~CTask()
{

}

bool CTask::isLeaf() const
{
    return true;
}
