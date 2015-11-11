#include "cprojectmanager.h"

CProjectManager::CProjectManager(QObject a_pParent)
    : QObject(a_pParent)
    , m_oModel()
{

}

CProjectManager::~CProjectManager()
{

}

QStandardItemModel *CProjectManager::getModel() const
{

}

void CProjectManager::prepareModel()
{
    QStandardItem *rootNode = m_oModel.invisibleRootItem();
}

