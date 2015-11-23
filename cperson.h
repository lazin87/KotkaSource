#ifndef CSUBJECT_H
#define CSUBJECT_H

#include <QString>
#include <QVariant>

#include "commonddefs.h"

class CPerson
{
public:
    enum EPersonPropertis
    {
        ePP_Invalid = -1,
        ePP_First = 0,
        ePP_Name = 0,
        ePP_Email,
        ePP_Phone,
        ePP_isWriter,
        ePP_isClient,

        ePP_NumberOfPropertis
    };

    explicit CPerson(QString const & a_strName);
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

    QVariant getPropertyData(EPersonPropertis a_eProperty) const;
    void setPropertyData(EPersonPropertis a_eProperty, const QVariant & a_rValue);

    static int getPropertyCount();
    static const QString s_aPropertisLabels[ePP_NumberOfPropertis];

    bool operator ==(const CPerson & a_rPerson);
private:
    // przerobic na strukture SContactData
    KotkaSource::SContactData m_ContactData;
    /*
    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;

    bool m_fIsWriter;
    bool m_fIsClient;
    */
};

#endif // CSUBJECT_H
