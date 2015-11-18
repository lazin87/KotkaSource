#include "cprojectbase.h"

CProjectBase::CProjectBase(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
{
    qWarning("CProjectBase::CProjectBase");
}

CProjectBase::~CProjectBase()
{
    qWarning("CProjectBase::~CProjectBase()");
    removeAllChildren();
}



bool CProjectBase::addChild(IProject *a_pChild)
{
    bool fResult = true;

    m_pProjectChildrens.append(a_pChild);

    return fResult;
}

IProject *CProjectBase::peekChild(int a_iIndex)
{
    IProject * pOutChild = 0;

    if( (0 <= a_iIndex) && (m_pProjectChildrens.count() > a_iIndex) )
    {
        pOutChild = m_pProjectChildrens.takeAt(a_iIndex);
    }
    else
    {
        qWarning("CMainProject::peekChild: wrong index: %d | array size: %d", a_iIndex, m_pProjectChildrens.count() );
    }

    return pOutChild;
}

bool CProjectBase::removeChild(int a_iIndex)
{
    bool fResult = false;
    IProject * pChild = peekChild(a_iIndex);

    if(0 != pChild)
    {
        fResult = true;
        delete pChild;
        pChild = 0;
    }

    return fResult;
}


void CProjectBase::removeAllChildren()
{
    while(false == m_pProjectChildrens.isEmpty() )
    {
        IProject * pChild = m_pProjectChildrens.takeLast();
        if(0 != pChild)
        {
            delete pChild;
            pChild = 0;
        }
    }
}


QStandardItem *CProjectBase::getStandardItem()
{
    int iRows = rowCount();
    qWarning("CProjectBase::getStandardItem(): %s, rows: %d",
             m_strName.toStdString().c_str(),
             iRows );

    foreach(IProject * pChild, m_pProjectChildrens)
    {
        appendRow(pChild->getStandardItem() );
    }

    return this;
}
