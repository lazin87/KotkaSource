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

void CProjectManager::removeProjects()
{
    foreach(IProject * pProject, m_pProjetsList)
    {
        if(0 != pProject)
        {
            delete pProject;
        }
    }
}

CProjectManager::~CProjectManager()
{
    qDebug() << "CProjectManager::~CProjectManager()";
    removeProjects();
}

QStandardItemModel *CProjectManager::getModel()
{
    prepareModel();

    return & m_oModel;
}

bool CProjectManager::createProject(QString a_strName)
{
    bool fResult  = false;

    m_pProjetsList.append(new CProjectBase(a_strName) );

    return fResult;
}

void CProjectManager::createProjectSlot(KotkaSource::SProjectData &a_rProjectData)
{
    IProject * pNewProject = new CProjectBase(a_rProjectData.m_strName);
    if(0 != pNewProject)
    {
        pNewProject->setDeadlineDelivery(a_rProjectData.m_oDateTimeDelivery);
        pNewProject->setDeadlineCopywriters(a_rProjectData.m_oDateTimeWriterDeadline);

        m_pProjetsList.append(pNewProject );

        QStandardItem *rootNode = m_oModel.invisibleRootItem();

        if(0 != rootNode)
        {
            rootNode->appendRow(pNewProject->getStandardItem() );
        }
        else
        {
            qDebug() << "CProjectManager::createProjectSlot(): QStandardItem NULL PTR";
        }
    }
    else
    {
        qDebug() << "CProjectManager::createProjectSlot(): IProject NULL PTR";
    }
}

void CProjectManager::createProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex)
{
    IProject * pNewProject = new CProjectBase(a_rProjectData.m_strName);
    if(0 != pNewProject)
    {
        pNewProject->setDeadlineDelivery(a_rProjectData.m_oDateTimeDelivery);
        pNewProject->setDeadlineCopywriters(a_rProjectData.m_oDateTimeWriterDeadline);

        if(a_rModelIndex.isValid() )
        {
            QStandardItem *pStandardItem = m_oModel.itemFromIndex(a_rModelIndex);
            pStandardItem->appendRow(pNewProject);

        }

        /*
        m_pProjetsList.append(pNewProject );

        QStandardItem *rootNode = m_oModel.invisibleRootItem();

        if(0 != rootNode)
        {
            rootNode->appendRow(pNewProject->getStandardItem() );
        }
        else
        {
            qDebug() << "CProjectManager::createProjectSlot(): QStandardItem NULL PTR";
        }
        */
    }
    else
    {
        qDebug() << "CProjectManager::createProjectSlot(): IProject NULL PTR";
    }


}

bool CProjectManager::createSubproject(IProject &a_rProject, QString a_strName)
{
    // to do
    a_rProject.addChild( new CProjectBase(a_strName, &a_rProject) );
    return false;
}

bool CProjectManager::createTask(IProject &a_rProject, QString a_strName)
{
    a_rProject.addChild(new CTask(a_strName, &a_rProject) );
    return false;
}

IProject *CProjectManager::getProject(int a_iIndex)
{
    // TO DO
    return m_pProjetsList[a_iIndex];
}


void CProjectManager::updateModelSlot()
{
    qDebug() << "CProjectManager::updateModelSlot()";
    emit projectModelWasChanged(getModel() );
}

void CProjectManager::prepareModel()
{
    m_oModel.clear(); // it calls items descturctors!!!
    QStandardItem *rootNode = m_oModel.invisibleRootItem();

    foreach(IProject * pProject, m_pProjetsList)
    {
        rootNode->appendRow(pProject->getStandardItem() );
    }
}

