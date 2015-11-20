#include "cperson.h"

#include "QDebug"

const QString CPerson::s_aPropertisLabels[] = {
      "Name"
    , "Email"
    , "Phone"
    , "Is Writer"
    , "Is Client"
};

CPerson::CPerson(QString const & a_strName)
    : m_strEmail()
    , m_strName(a_strName)
    , m_strPhone()
    , m_fIsWriter(false)
    , m_fIsClient(false)
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
    qDebug("CSubject::setStrEmail: %s -> %s", m_strEmail.toLatin1().data(), strEmail.toLatin1().data() );
    m_strEmail = strEmail;
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
    qDebug("CSubject::setStrPhone: %s -> %s", m_strPhone.toLatin1().data(), strPhone.toLatin1().data() );
    m_strPhone = strPhone;
}

void CPerson::setIsWriter(bool a_fIsWriter)
{
    m_fIsWriter = a_fIsWriter;
}

void CPerson::setIsClient(bool a_fIsClient)
{
    m_fIsClient = a_fIsClient;
}

QVariant CPerson::getPropertyData(CPerson::EPersonPropertis a_eProperty) const
{
    switch(a_eProperty)
    {
    case ePP_Name:
        return m_strName;

    case ePP_Email:
        return m_strEmail;

    case ePP_Phone:
        return m_strPhone;

    case ePP_isClient:
        return m_fIsClient;

    case ePP_isWriter:
        return m_fIsWriter;

    default:
        return QVariant();
    }
}

int CPerson::getPropertyCount()
{
    return static_cast<int>(ePP_NumberOfPropertis);
}




