#include "ctask.h"

CTask::CTask(QString a_strName)
    : IProject(a_strName)
    , m_sData()
{
    m_sData.m_strName = a_strName;
    m_sData.m_strParentName = "";
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

QString CTask::getName() const
{
    return m_sData.m_strName;
}

QString CTask::getParentName() const
{
    return m_sData.m_strParentName;
}

QDateTime CTask::deadlineDelivery() const
{
    QDateTime oOutDateTime = m_sData.m_oDateTimeDelivery;

    if(false == oOutDateTime.isValid() )
    {
        QStandardItem * pParentItem = parent();

        if( 0 != pParentItem )
        {
            oOutDateTime = pParentItem->data(KotkaSource::DeliveryDateRole).toDateTime();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

void CTask::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
{
    m_sData.m_oDateTimeDelivery = a_rDeadlineDelivery;
}

QDateTime CTask::deadlineCopywriters() const
{
    QDateTime oOutDateTime = m_sData.m_oDateTimeWriterDeadline;

    if(false == oOutDateTime.isValid() )
    {
        QStandardItem * pParentItem = parent();

        if( 0 != pParentItem )
        {
            oOutDateTime = pParentItem->data(KotkaSource::WritersDeadlineDateRole).toDateTime();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

void CTask::setName(const QString &a_rName)
{
    m_sData.m_strName = a_rName;
}

void CTask::setParentName(const QString &a_rParentName)
{
    m_sData.m_strParentName = a_rParentName;
}

void CTask::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
{
    m_sData.m_oDateTimeWriterDeadline = a_rDeadlineCopywriters;
}

QVariant CTask::data(int a_iRole) const
{
    if(KotkaSource::ReadTaskDataRole == a_iRole)
    {
        return QVariant::fromValue(m_sData);
    }

    return IProject::data(a_iRole);
}
void CTask::setData(const QVariant &a_value, int a_iRole)
{
    IProject::setData(a_value, a_iRole);
}
