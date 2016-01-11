#include "ctask.h"

#include <QDebug>

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
                qWarning() << "CProject::deadlineDelivery(): invalid";
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
                qWarning() << "CProject::deadlineDelivery(): invalid";
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

void CTask::fillInTaskData(const KotkaSource::STaskData &a_rTaskData)
{
    m_sData.m_strName = (a_rTaskData.m_strName == noChange<QString>() ) ? m_sData.m_strName : a_rTaskData.m_strName;
    m_sData.m_strParentName = (a_rTaskData.m_strParentName == noChange<QString>() ) ? m_sData.m_strParentName : a_rTaskData.m_strParentName;
    m_sData.m_strDesc = (a_rTaskData.m_strDesc == noChange<QString>() ) ? m_sData.m_strDesc : a_rTaskData.m_strDesc;
    m_sData.m_strWriterName = (a_rTaskData.m_strWriterName == noChange<QString>() ) ? m_sData.m_strWriterName : a_rTaskData.m_strWriterName;
    m_sData.m_oDateTimeDelivery = (a_rTaskData.m_oDateTimeDelivery == noChange<QDateTime>() ) ? m_sData.m_oDateTimeDelivery : a_rTaskData.m_oDateTimeDelivery;
    m_sData.m_oDateTimeWriterDeadline = (a_rTaskData.m_oDateTimeWriterDeadline == noChange<QDateTime>() ) ? m_sData.m_oDateTimeWriterDeadline : a_rTaskData.m_oDateTimeWriterDeadline;
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
    if(KotkaSource::WriteTaskDataRole == a_iRole)
    {
        KotkaSource::STaskData oTaskData = a_value.value<KotkaSource::STaskData>();
        fillInTaskData(oTaskData);
    }
    else
    {
        IProject::setData(a_value, a_iRole);
    }
}
