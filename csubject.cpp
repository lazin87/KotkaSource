#include "csubject.h"

#include "QDebug"
CSubject::CSubject(QString const & a_strEmail)
    : m_strEmail(a_strEmail)
    , m_strName()
    , m_strPhone()
{

}

CSubject::~CSubject()
{

}
QString CSubject::strEmail() const
{
    return m_strEmail;
}

void CSubject::setStrEmail(const QString &strEmail)
{
    if(validEmail(strEmail) )
    {
        qDebug("CSubject::setStrEmail: %s -> %s", m_strEmail.toLatin1().data(), strEmail.toLatin1().data() );
        m_strEmail = strEmail;
    }
    else
    {
        qWarning("CSubject::setStrEmail: invalid value: %s", strEmail.toLatin1().data() );
    }
}
QString CSubject::strName() const
{
    return m_strName;
}

void CSubject::setStrName(const QString &strName)
{
    qDebug("CSubject::setStrName: %s -> %s", m_strName.toLatin1().data(), strName.toLatin1().data() );
    m_strName = strName;
}
QString CSubject::strPhone() const
{
    return m_strPhone;
}

void CSubject::setStrPhone(const QString &strPhone)
{
    if(validPhone(strPhone) )
    {
        qDebug("CSubject::setStrPhone: %s -> %s", m_strPhone.toLatin1().data(), strPhone.toLatin1().data() );
        m_strPhone = strPhone;
    }
    else
    {
        qWarning("CSubject::setStrPhone: invalid value: %s", strPhone.toLatin1().data() );
    }
}

bool CSubject::validEmail(const QString &a_rEmail)
{
    bool fResult = false;

    return fResult;
}

bool CSubject::validPhone(const QString &a_rPhone)
{
    bool fResult = false;

    return fResult;
}




