#include "cprojectbase.h"

CProjectBase::CProjectBase(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
{

}

CProjectBase::~CProjectBase()
{
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
    foreach(IProject * pChild, m_pProjectChildrens)
    {
        appendRow(pChild->getStandardItem() );
    }

    return this;
}
/*
QVariant CProjectBase::data(int a_iRole) const
{
    switch(a_iRole)
    {

    case KotkaSource::ProjectDescDispRole:
    {
        QString strData = "Name: " + strName()
                + "\nType: " + QString( (0 == m_pProjectParent) ? "Main project" : "Sub project")
                + "\nDelivery: " + deadlineDelivery().toString()
                + "\nDeadline for copywriters: " + deadlineCopywriters().toString();

        return strData;
    }

    case KotkaSource::DeliveryDateRole:
    {
        return deadlineDelivery();
    }

    case KotkaSource::DeadlineDateRole:
    {
        return deadlineCopywriters();
    }

    case KotkaSource::ObjectNameRole:
    {
        return m_strName;
    }

    case KotkaSource::ObjectTypeRole:
    {
        return QString( (0 == m_pProjectParent) ? "Main project" : "Subproject");
    }

    default:
        return IProject::data(a_iRole);
    }
}
*/
