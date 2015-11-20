#ifndef CSUBJECT_H
#define CSUBJECT_H

#include <QString>
#include <QVariant>

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

    void setIsWriter(bool a_fIsWriter);
    void setIsClient(bool a_fIsClient);

    QVariant getPropertyData(EPersonPropertis a_eProperty) const;
    static int getPropertyCount();

    static const QString s_aPropertisLabels[ePP_NumberOfPropertis];

private:
    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;

    bool m_fIsWriter;
    bool m_fIsClient;
};

#endif // CSUBJECT_H
