#include "ctask.h"

CTask::CTask(QString a_strName)
    : IProject(a_strName)
    , m_sData()
{
    m_sData.m_strName = a_strName;
}

CTask::CTask(const KotkaSource::STaskData &a_rTaskData)
    : IProject(a_rTaskData.m_strName)
{
    m_sData = a_rTaskData;
}

CTask::~CTask()
{

}

bool CTask::isLeaf() const
{
    return true;
}
