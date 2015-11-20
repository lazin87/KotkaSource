#ifndef CSUBJECT_H
#define CSUBJECT_H

#include <QString>
#include <QVariant>

class CPerson
{
public:
    enum EPersonPropertis
    {
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

    QVariant getPropertyData(EPersonPropertis a_iProperty) const;
    static int getPropertyCount();

    static const QString s_aPropertisLabels[ePP_NumberOfPropertis];

private:
    bool validEmail(QString const & a_rEmail);
    bool validPhone(QString const & a_rPhone);

    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;
};

#endif // CSUBJECT_H
