#include "cprojectbase.h"

#include "ctask.h"

CProjectBase::CProjectBase(QString a_strName)
    : IProject(a_strName)
    , m_sData()
    , m_oSourceModel(a_strName)
{
    m_sData.m_strName = a_strName;
    m_sData.m_strParentName = "";
}

CProjectBase::CProjectBase(const KotkaSource::SProjectData &a_crProjectData)
    : IProject(a_crProjectData.m_strName)
    , m_sData(a_crProjectData)
    , m_oSourceModel(a_crProjectData.m_strName)
{

}

CProjectBase::~CProjectBase()
{
}

QString CProjectBase::getName() const
{
    return m_sData.m_strName;
}

QString CProjectBase::getParentName() const
{
    return m_sData.m_strParentName;
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

void CProjectBase::setParentName(const QString &a_rParentName)
{
    m_sData.m_strParentName = a_rParentName;
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
    QList<CSourcesModel::T_SourceTaskDataPair> sourceAndTasksDataPairList;

    m_oSourceModel.getTaskListFromSources(sourceAndTasksDataPairList);

    foreach(CSourcesModel::T_SourceTaskDataPair sourceAndTasksDataPair, sourceAndTasksDataPairList)
    {
        IProject * pNewSubProject = new CProjectBase(sourceAndTasksDataPair.first);
        if(0 != pNewSubProject)
        {
            foreach(KotkaSource::STaskData taskData, sourceAndTasksDataPair.second)
            {
                IProject * pNewTask = new CTask(taskData);
                if(0 != pNewTask)
                {
                    pNewSubProject->appendRow(pNewTask);
                }
            }

            appendRow(pNewSubProject);
        }
        /*
        qDebug("CProjectBase::parseSources(): create task: %d, name: %s", taskData.m_iId, taskData.m_strName.toLatin1().data() );
        IProject * pNewTask = new CTask(taskData);
        if(0 != pNewTask)
        {
            appendRow(pNewTask);
        }
        */
    }
}

void CProjectBase::fillInProjectData(const KotkaSource::SProjectData &a_rProjectData)
{
    m_sData.m_strName = (a_rProjectData.m_strName == noChange<QString>() ) ? m_sData.m_strName : a_rProjectData.m_strName;
    m_sData.m_strParentName = (a_rProjectData.m_strParentName == noChange<QString>() ) ? m_sData.m_strParentName : a_rProjectData.m_strParentName;
    m_sData.m_oDateTimeDelivery = (a_rProjectData.m_oDateTimeDelivery == noChange<QDateTime>() ) ? m_sData.m_oDateTimeDelivery : a_rProjectData.m_oDateTimeDelivery;
    m_sData.m_oDateTimeWriterDeadline = (a_rProjectData.m_oDateTimeWriterDeadline == noChange<QDateTime>() ) ? m_sData.m_oDateTimeWriterDeadline : a_rProjectData.m_oDateTimeWriterDeadline;
    m_sData.m_strClientName = (a_rProjectData.m_strClientName == noChange<QString>() ) ? m_sData.m_strClientName : a_rProjectData.m_strClientName;
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
    if(KotkaSource::WriteProjectDataRole == a_iRole)
    {
        KotkaSource::SProjectData oProjectData = a_value.value<KotkaSource::SProjectData>();
        fillInProjectData(oProjectData);
    }
    else
    {
        IProject::setData(a_value, a_iRole);
    }
}
