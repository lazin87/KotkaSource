#include "cprojectmanager.h"

#include "iproject.h"
#include "cprojectbase.h"
#include "ctask.h"

#include<QDebug>

CProjectManager::CProjectManager(QObject * a_pParent)
    : QObject(a_pParent)
    , m_oModel()
{

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

void CProjectManager::prepareModel()
{
    QStandardItem *rootNode = m_oModel.invisibleRootItem();
    foreach(IProject * pProject, m_pProjetsList)
    {
        rootNode->appendRow(pProject->getStandardItem() );
    }
}

