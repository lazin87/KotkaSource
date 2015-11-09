#ifndef CPROJECT_H
#define CPROJECT_H

#include <QString>
#include <QDateTime>

class CProject
{
public:
    explicit CProject(QString a_strName, const CProject * a_pProjectParent = 0);
    virtual ~CProject();

    QString strName() const;
    void setStrName(const QString &a_rstrName);

    QDateTime deadlineDelivery() const;
    void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery);

    QDateTime deadlineCopywriters() const;
    void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters);

protected:
    const CProject * m_pProjectParent;

    QString m_strName;

    QDateTime m_oDeadlineDelivery;
    QDateTime m_oDeadlineCopywriters;
};

#endif // CPROJECT_H
