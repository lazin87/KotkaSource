#ifndef CPROJECT_H
#define CPROJECT_H

#include <QString>
#include <QDateTime>
#include <QStandardItem>

#include "commonddefs.h"

class IProject : public QStandardItem
{
public:
    explicit IProject(QString a_strName, const IProject * a_pProjectParent = 0);
    virtual ~IProject();

    virtual bool isLeaf() const;

    virtual QVariant data(int a_iRole) const;
    virtual void setData(const QVariant &a_value, int a_iRole);

    QDateTime deadlineDelivery() const;
    QDateTime deadlineCopywriters() const;
    void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery);
    void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters);

protected:
   QString m_strName;

    QDateTime m_oDeadlineDelivery;
    QDateTime m_oDeadlineCopywriters;

    // TO DO dodac membera do przechowywania zrodel
};

#endif // CPROJECT_H
