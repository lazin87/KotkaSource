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

void CProjectManager::createProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex)
{
    IProject * pNewProject = new CProjectBase(a_rProjectData.m_strName);
    if(0 != pNewProject)
    {
        pNewProject->setDeadlineDelivery(a_rProjectData.m_oDateTimeDelivery);
        pNewProject->setDeadlineCopywriters(a_rProjectData.m_oDateTimeWriterDeadline);

        QStandardItem *pStandardItem = (a_rModelIndex.isValid() ) ? m_oModel.itemFromIndex(a_rModelIndex)
                                                                  : m_oModel.invisibleRootItem();
        pStandardItem->appendRow(pNewProject);
    }
    else
    {
        qDebug() << "CProjectManager::createProjectSlot(): IProject NULL PTR";
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

void CProjectManager::updateModelSlot()
{
    qDebug() << "CProjectManager::updateModelSlot()";
    emit projectModelWasChanged(getModel() );
}
