#include "cperson.h"

#include "QDebug"
CPerson::CPerson(QString const & a_strEmail)
    : m_strEmail(a_strEmail)
    , m_strName()
    , m_strPhone()
{

}

CPerson::~CPerson()
{

}
QString CPerson::strEmail() const
{
    return m_strEmail;
}

void CPerson::setStrEmail(const QString &strEmail)
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
QString CPerson::strName() const
{
    return m_strName;
}

void CPerson::setStrName(const QString &strName)
{
    qDebug("CSubject::setStrName: %s -> %s", m_strName.toLatin1().data(), strName.toLatin1().data() );
    m_strName = strName;
}
QString CPerson::strPhone() const
{
    return m_strPhone;
}

void CPerson::setStrPhone(const QString &strPhone)
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

bool CPerson::validEmail(const QString &a_rEmail)
{
    bool fResult = false;

    return fResult;
}

bool CPerson::validPhone(const QString &a_rPhone)
{
    bool fResult = false;

    return fResult;
}




