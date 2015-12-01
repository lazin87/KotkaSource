#include "cprojectbase.h"

#include "ctask.h"

CProjectBase::CProjectBase(QString a_strName)
    : IProject(a_strName)
    , m_sData()
    , m_oSourceModel(a_strName)
{
    m_sData.m_strName = a_strName;
}

CProjectBase::~CProjectBase()
{
}

QString CProjectBase::getName() const
{
    return m_sData.m_strName;
}

QDateTime CProjectBase::deadlineDelivery() const
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

void CProjectBase::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
{
    m_sData.m_oDateTimeDelivery = a_rDeadlineDelivery;
}

QDateTime CProjectBase::deadlineCopywriters() const
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

void CProjectBase::setName(const QString &a_rName)
{
    m_sData.m_strName = a_rName;
}

void CProjectBase::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
{
    m_sData.m_oDateTimeWriterDeadline = a_rDeadlineCopywriters;
}

void CProjectBase::fillInSourcesModel(const QList<KotkaSource::SSourceData> &a_rSourceList)
{
    foreach(KotkaSource::SSourceData sourceData, a_rSourceList)
    {
        m_oSourceModel.addNewSource(sourceData.m_strName, sourceData.m_fReadOnly, sourceData.m_strParserName);
    }
}

void CProjectBase::parseSources()
{
    qDebug("CProjectBase::parseSources()" );
    QList<KotkaSource::STaskData> oTaskDataList;
    m_oSourceModel.getTaskListFromSources(oTaskDataList);

    foreach(KotkaSource::STaskData taskData, oTaskDataList)
    {
        qDebug("CProjectBase::parseSources(): create task: %d, name: %s", taskData.m_iId, taskData.m_strName.toLatin1().data() );
        IProject * pNewTask = new CTask(taskData);
        if(0 != pNewTask)
        {
            appendRow(pNewTask);
        }
    }
}

QVariant CProjectBase::data(int a_iRole) const
{
    if(KotkaSource::ReadProjectDataRole == a_iRole)
    {
        return QVariant::fromValue(m_sData);
    }

    return IProject::data(a_iRole);
}
void CProjectBase::setData(const QVariant &a_value, int a_iRole)
{
    IProject::setData(a_value, a_iRole);
}
