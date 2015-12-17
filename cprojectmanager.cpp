#include "cprojectmanager.h"

#include "iproject.h"
#include "cprojectbase.h"
#include "ctask.h"

#include<QDebug>
#include<QMultiMap>

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
        pNewProject->setParentName("TO BE DONE");

        emit projectWasCreated(a_rProjectData);
    }
    else
    {
        qDebug() << "CProjectManager::createProjectSlot(): IProject NULL PTR";
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

void CProjectManager::loadProjectHierarchy(const QList<KotkaSource::SProjectData> &a_crProjectDataList)
{
    m_oModel.clear();

    QMultiMap<QString, IProject *> mapOfProjectByParent;
    foreach(KotkaSource::SProjectData const & sProjectData, a_crProjectDataList)
    {
        mapOfProjectByParent.insert(sProjectData.m_strParentName, new CProjectBase(sProjectData) );
    }

    QStandardItem *pStdItem = m_oModel.invisibleRootItem();
    QList<IProject *> projectList = mapOfProjectByParent.values("");
    pStdItem->appendRow(projectList[0]);
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
