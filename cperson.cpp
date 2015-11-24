#include "cperson.h"

#include "QDebug"

CPerson::CPerson(QString const & a_strName)
    : m_ContactData()
{
    m_ContactData.m_strName = a_strName;
    m_ContactData.m_fIsClient = false;
    m_ContactData.m_fIsWriter = false;
}

CPerson::CPerson(const KotkaSource::SContactData &a_rContactData)
    : m_ContactData(a_rContactData)
{

}

CPerson::~CPerson()
{

}
QString CPerson::strEmail() const
{
    return m_ContactData.m_strEmail;
}

void CPerson::setStrEmail(const QString &strEmail)
{
    qDebug("CSubject::setStrEmail: %s -> %s", m_ContactData.m_strEmail.toLatin1().data(), strEmail.toLatin1().data() );
    m_ContactData.m_strEmail = strEmail;
}
QString CPerson::strName() const
{
    return m_ContactData.m_strName;
}

void CPerson::setStrName(const QString &strName)
{
    qDebug("CSubject::setStrName: %s -> %s", m_ContactData.m_strName.toLatin1().data(), strName.toLatin1().data() );
    m_ContactData.m_strName = strName;
}
QString CPerson::strPhone() const
{
    return m_ContactData.m_strPhone;
}

void CPerson::setStrPhone(const QString &strPhone)
{
    qDebug("CSubject::setStrPhone: %s -> %s", m_ContactData.m_strPhone.toLatin1().data(), strPhone.toLatin1().data() );
    m_ContactData.m_strPhone = strPhone;
}

QString CPerson::strAddress() const
{
    return m_ContactData.m_strName + " address";
}

void CPerson::setIsWriter(bool a_fIsWriter)
{
    m_ContactData.m_fIsWriter = a_fIsWriter;
}

bool CPerson::isWriter() const
{
    return m_ContactData.m_fIsWriter;
}

void CPerson::setIsClient(bool a_fIsClient)
{
    m_ContactData.m_fIsClient = a_fIsClient;
}

bool CPerson::isClient() const
{
    return m_ContactData.m_fIsClient;
}

KotkaSource::SContactData CPerson::getContactData() const
{
    return m_ContactData;
}

QVariant CPerson::getPropertyData(CPersonPropertis::EPersonPropertis a_eProperty) const
{
    switch(a_eProperty)
    {
    case CPersonPropertis::eName:
        return m_ContactData.m_strName;

    case CPersonPropertis::eEmail:
        return m_ContactData.m_strEmail;

    case CPersonPropertis::ePhone:
        return m_ContactData.m_strPhone;

    case CPersonPropertis::eIsClient:
        return m_ContactData.m_fIsClient;

    case CPersonPropertis::eIsWriter:
        return m_ContactData.m_fIsWriter;

    default:
        return QVariant();
    }
}

void CPerson::setPropertyData(CPersonPropertis::EPersonPropertis a_eProperty, const QVariant &a_rValue)
{
    switch(a_eProperty)
    {
    case CPersonPropertis::eName:
        m_ContactData.m_strName = a_rValue.toString();
        break;

    case CPersonPropertis::eEmail:
        m_ContactData.m_strEmail = a_rValue.toString();
        break;

    case CPersonPropertis::ePhone:
        m_ContactData.m_strPhone = a_rValue.toString();
        break;

    case CPersonPropertis::eIsClient:
        m_ContactData.m_fIsClient = a_rValue.toBool();
        break;

    case CPersonPropertis::eIsWriter:
        m_ContactData.m_fIsWriter = a_rValue.toBool();
        break;
    }
}

bool CPerson::operator ==(const CPerson &a_rPerson)
{
    return (0 == m_ContactData.m_strName.compare(a_rPerson.m_ContactData.m_strName,Qt::CaseInsensitive) );
}
