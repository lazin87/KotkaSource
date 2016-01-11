#include "cprojectmanager.h"

#include "iproject.h"
#include "cprojectbase.h"
#include "ctask.h"

#include<QDebug>


CProjectManager::CProjectManager(QObject * a_pParent)
    : QObject(a_pParent)
    , m_oModel()
{
    connect( &m_oModel, SIGNAL(itemChanged(QStandardItem*) )
           , this, SLOT(updateModelSlot() )
           );

    prepareDirs();
}


CProjectManager::~CProjectManager()
{
    qDebug() << "CProjectManager::~CProjectManager()";
}

QStandardItemModel *CProjectManager::getModel()
{
    return & m_oModel;
}

bool CProjectManager::createProject(QString a_strName)
{
    bool fResult  = false;

    return fResult;
}

void CProjectManager::createProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex, QList<KotkaSource::SSourceData> &a_rSourcesDataList)
{
    IProject * pNewProject = new CProjectBase(a_rProjectData.m_strName);
    if(0 != pNewProject)
    {
        pNewProject->setDeadlineDelivery(a_rProjectData.m_oDateTimeDelivery);
        pNewProject->setDeadlineCopywriters(a_rProjectData.m_oDateTimeWriterDeadline);
        pNewProject->fillInSourcesModel(a_rSourcesDataList);

        // TYMCZASOWO
        pNewProject->parseSources();
        // END TYMCZASOWO

        QStandardItem *pStandardItem = (a_rModelIndex.isValid() ) ? m_oModel.itemFromIndex(a_rModelIndex)
                                                                  : m_oModel.invisibleRootItem();
        pStandardItem->appendRow(pNewProject);

        emit projectWasCreated(a_rProjectData);
    }
    else
    {
        qDebug() << "CProjectManager::createProjectSlot(): IProject NULL PTR";
    }
}

void CProjectManager::editProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex, QList<KotkaSource::SSourceData> &a_rSourcesDataList)
{
    qDebug() << "CProjectManager::editProjectSlot";
    if(a_rModelIndex.isValid() )
    {
        QVariant value = QVariant::fromValue(a_rProjectData );
        m_oModel.setData(a_rModelIndex, value, KotkaSource::WriteProjectDataRole);
    }
    else
    {
        qWarning() << "CProjectManager::editProjectSlot: index is invalid";
    }

}

void CProjectManager::createTaskSlot(KotkaSource::STaskData &a_rTaskData, QModelIndex &a_rModelIndex)
{
    qDebug() << "CProjectManager::createTaskSlot()";
    IProject * pNewTask = new CTask(a_rTaskData);
    if( (0 != pNewTask) && a_rModelIndex.isValid() )
    {
        QStandardItem *pStandardItem = m_oModel.itemFromIndex(a_rModelIndex);
        pStandardItem->appendRow(pNewTask);
        pNewTask->setParentName("TO BE DONE");

        emit taskWasCreated(a_rTaskData);
    }
    else
    {
        qWarning() << "CProjectManager::createTaskSlot(): ERR: IndexValid: " << a_rModelIndex.isValid();
    }
}

void CProjectManager::editTaskSlot(KotkaSource::STaskData &a_rTaskData, QModelIndex &a_rModelIndex)
{
    qDebug() << "CProjectManager::editTaskSlot";
    if(a_rModelIndex.isValid() )
    {
        QVariant value = QVariant::fromValue(a_rTaskData );
        m_oModel.setData(a_rModelIndex, value, KotkaSource::WriteTaskDataRole);
    }
    else
    {
        qWarning() << "CProjectManager::editTaskSlot: index is invalid";
    }
}

bool CProjectManager::createSubproject(IProject &a_rProject, QString a_strName)
{
    // to do
    return false;
}

bool CProjectManager::createTask(IProject &a_rProject, QString a_strName)
{
    // to do
    return false;
}

void CProjectManager::loadProjectsModel(const QList<KotkaSource::SProjectData> &a_crProjectDataList, const QList<KotkaSource::STaskData> &a_crTasksDataList, const QList<KotkaSource::SSourceData> &a_crSourcesData)
{
    m_oModel.clear();

    QMap<QString, QStandardItem *> mapOfProjectbyName;
    if(!a_crProjectDataList.isEmpty() )
    {
        buildProjectsHierarchy(a_crProjectDataList, mapOfProjectbyName);
    }

    if(!a_crTasksDataList.isEmpty() && !mapOfProjectbyName.isEmpty() )
    {
        addTasksToProjectHierarchy(a_crTasksDataList, mapOfProjectbyName);
    }

    if(!a_crSourcesData.isEmpty() && !mapOfProjectbyName.isEmpty() )
    {
        addSourcesToProjectHierarchy(a_crSourcesData, mapOfProjectbyName);
    }
}

void CProjectManager::updateModelSlot()
{
    qDebug() << "CProjectManager::updateModelSlot()";
    emit projectModelWasChanged(getModel() );
}

void CProjectManager::prepareDirs()
{
    QDir oDir;
    oDir.mkdir(KotkaSource::strMAIN_APP_PATH);
    oDir.mkdir(KotkaSource::strINPUT_FILES_PATH);
    oDir.mkdir(KotkaSource::strOUTPUT_FILES_PATH);
}

void CProjectManager::buildProjectsHierarchy(const QList<KotkaSource::SProjectData> &a_crProjectDataList, QMap<QString, QStandardItem *> & a_rMapOfProjectbyName)
{
    QMultiMap<QString, QStandardItem *> mapOfProjectByParent;
    foreach(KotkaSource::SProjectData const & sProjectData, a_crProjectDataList)
    {
        QStandardItem * pStdItem = new CProjectBase(sProjectData);
        mapOfProjectByParent.insert(sProjectData.m_strParentName, pStdItem);
        a_rMapOfProjectbyName.insert(sProjectData.m_strName, pStdItem);
    }

    const QList<QString> parentNames = mapOfProjectByParent.uniqueKeys();
    foreach(QString const & parentName, parentNames)
    {
        if("" != parentName)
        {
            a_rMapOfProjectbyName[parentName]->appendRows(mapOfProjectByParent.values(parentName) );
        }
    }

    QStandardItem *pRootItem = m_oModel.invisibleRootItem();
    pRootItem->appendRows(mapOfProjectByParent.values(""));
}

void CProjectManager::addTasksToProjectHierarchy(const QList<KotkaSource::STaskData> &a_crTasksDataList, QMap<QString, QStandardItem *> & a_rMapOfProjectbyName)
{
    QMultiMap<QString, QStandardItem *> multiMapOfTasksByParent;

    foreach(KotkaSource::STaskData const & taskData, a_crTasksDataList)
    {
        if(false == taskData.m_strParentName.isEmpty() )
        {
            QStandardItem * pStdItem = new CTask(taskData);
            multiMapOfTasksByParent.insert(taskData.m_strParentName, pStdItem);
        }
    }

    const QList<QString> parentNames = multiMapOfTasksByParent.uniqueKeys();
    foreach(QString const & parentName, parentNames)
    {
        if("" != parentName)
        {
            a_rMapOfProjectbyName[parentName]->appendRows(multiMapOfTasksByParent.values(parentName) );
        }
    }
}

void CProjectManager::addSourcesToProjectHierarchy(const QList<KotkaSource::SSourceData> &a_crSourcesData, QMap<QString, QStandardItem *> &a_rMapOfProjectbyName)
{
    QMultiMap<QString, KotkaSource::SSourceData> multiMapOfSourcesByParent;

    foreach(KotkaSource::SSourceData oSourceData, a_crSourcesData)
    {
        if(false == oSourceData.m_strParent.isEmpty() )
        {
            multiMapOfSourcesByParent.insert(oSourceData.m_strParent, oSourceData);
        }
    }

    const QList<QString> parentNames = multiMapOfSourcesByParent.uniqueKeys();
    foreach(QString const & parentName, parentNames)
    {
        CProjectBase * pProject = static_cast<CProjectBase *>(a_rMapOfProjectbyName[parentName] );
        if(0 != pProject)
        {
            pProject->fillInSourcesModel(multiMapOfSourcesByParent.values(parentName) );
        }
    }
}
