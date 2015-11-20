#ifndef CSUBJECT_H
#define CSUBJECT_H

#include <QString>

class CPerson
{
public:
    explicit CPerson(QString const & a_strEmail);
    ~CPerson();

    QString strEmail() const;
    void setStrEmail(const QString &strEmail);

    QString strName() const;
    void setStrName(const QString &strName);

    QString strPhone() const;
    void setStrPhone(const QString &strPhone);

private:
    bool validEmail(QString const & a_rEmail);
    bool validPhone(QString const & a_rPhone);

    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;
};

#endif // CSUBJECT_H
