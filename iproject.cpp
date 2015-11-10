#include "iproject.h"

#include <QDebug>

IProject::IProject(QString a_strName, const IProject *a_pProjectParent)
    : m_pProjectParent(a_pProjectParent)
    , m_strName(a_strName)
    , m_oDeadlineDelivery()
    , m_oDeadlineCopywriters()
{

}

IProject::~IProject()
{

}

bool IProject::isLeaf() const
{
    return false;
}

QString IProject::strName() const
{
    return m_strName;
}

void IProject::setStrName(const QString &a_rstrName)
{
    m_strName = a_rstrName;
}

QDateTime IProject::deadlineDelivery() const
{
    QDateTime oOutDateTime = m_oDeadlineDelivery;

    if(false == oOutDateTime.isValid() )
    {
        if( 0 != m_pProjectParent )
        {
            oOutDateTime = m_pProjectParent->deadlineDelivery();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

void IProject::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
{
    m_oDeadlineDelivery = a_rDeadlineDelivery;
}

QDateTime IProject::deadlineCopywriters() const
{
    QDateTime oOutDateTime = m_oDeadlineCopywriters;

    if(false == oOutDateTime.isValid() )
    {
        if( 0 != m_pProjectParent )
        {
            oOutDateTime = m_pProjectParent->deadlineCopywriters();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

void IProject::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
{
    m_oDeadlineCopywriters = a_rDeadlineCopywriters;
}




