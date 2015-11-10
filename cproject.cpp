#include "cproject.h"

#include <QDebug>

CProject::CProject(QString a_strName, const CProject *a_pProjectParent)
    : m_pProjectParent(a_pProjectParent)
    , m_strName(a_strName)
    , m_oDeadlineDelivery()
    , m_oDeadlineCopywriters()
{

}

CProject::~CProject()
{

}

bool CProject::isLeaf() const
{
    return false;
}

QString CProject::strName() const
{
    return m_strName;
}

void CProject::setStrName(const QString &a_rstrName)
{
    m_strName = a_rstrName;
}

QDateTime CProject::deadlineDelivery() const
{
    const QDateTime * ptrOutDateTime = &m_oDeadlineDelivery;

    if(false == m_oDeadlineDelivery.isValid() )
    {
        if( 0 != m_pProjectParent )
        {
            ptrOutDateTime = &(m_pProjectParent->deadlineDelivery() );

            if(false == ptrOutDateTime->isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return *ptrOutDateTime;
}

void CProject::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
{
    m_oDeadlineDelivery = a_rDeadlineDelivery;
}

QDateTime CProject::deadlineCopywriters() const
{
    const QDateTime * ptrOutDateTime = &m_oDeadlineCopywriters;

    if(false == m_oDeadlineCopywriters.isValid() )
    {
        if( 0 != m_pProjectParent )
        {
            ptrOutDateTime = &(m_pProjectParent->deadlineCopywriters() );

            if(false == ptrOutDateTime->isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return *ptrOutDateTime;
}

void CProject::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
{
    m_oDeadlineCopywriters = a_rDeadlineCopywriters;
}




