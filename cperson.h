#ifndef CSUBJECT_H
#define CSUBJECT_H

#include <QString>
#include <QVariant>

#include "commonddefs.h"

class CPerson
{
public:
    explicit CPerson(QString const & a_strName);
    explicit CPerson(KotkaSource::SContactData const & a_rContactData);
    ~CPerson();

    QString strEmail() const;
    void setStrEmail(const QString &strEmail);

    QString strName() const;
    void setStrName(const QString &strName);

    QString strPhone() const;
    void setStrPhone(const QString &strPhone);

    QString strAddress() const;

    void setIsWriter(bool a_fIsWriter);
    bool isWriter() const;

    void setIsClient(bool a_fIsClient);
    bool isClient() const;

    KotkaSource::SContactData getContactData() const;
    void setData(KotkaSource::SContactData const & a_rContactData);

    QVariant getPropertyData(CPersonPropertis::EPersonPropertis a_eProperty) const;
    void setPropertyData(CPersonPropertis::EPersonPropertis a_eProperty, const QVariant & a_rValue);

    bool operator ==(const CPerson & a_rPerson);
private:
    KotkaSource::SContactData m_ContactData;
};

#endif // CSUBJECT_H
