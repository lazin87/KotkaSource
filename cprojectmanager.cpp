#include "cprojectmanager.h"

#include "iproject.h"
#include "cmainproject.h"

CProjectManager::CProjectManager(QObject * a_pParent)
    : QObject(a_pParent)
    , m_oModel()
{

}

CProjectManager::~CProjectManager()
{

}

QStandardItemModel *CProjectManager::getModel()
{
    prepareModel();

    return & m_oModel;
}

bool CProjectManager::createProject(QString a_strName)
{
    bool fResult  = false;

    m_pProjetsList.append(new CMainProject(a_strName) );

    return fResult;
}

bool CProjectManager::createSubproject(IProject &a_rProject, QString a_strName)
{
    // to do
    a_rProject.addChild( new CMainProject(a_strName) );
    return false;
}

bool CProjectManager::createTask(IProject &a_rProject)
{
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

