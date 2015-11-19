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


QStandardItem *CTask::getStandardItem()
{
    return this;
}

/*
QVariant CTask::data(int a_iRole) const
{
    if(KotkaSource::ProjectDescDispRole == a_iRole)
    {
        QString strData = "Name: " + strName()
                        + "\nType: Task"
                        + "\nDelivery: " + deadlineDelivery().toString()
                        + "\nDeadline for copywriters: " + deadlineCopywriters().toString();

        return strData;
    }

    return IProject::data(a_iRole);
}
*/
