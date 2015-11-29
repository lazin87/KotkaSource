#ifndef CTASK_H
#define CTASK_H

#include "iproject.h"

#include "commonddefs.h"

class CTask : public IProject
{
public:
    explicit CTask(QString a_strName);
    explicit CTask(KotkaSource::STaskData const & a_rTaskData);

    ~CTask();

    virtual QVariant data(int a_iRole) const;
    virtual void setData(const QVariant &a_value, int a_iRole);

    // IProject interface
    virtual bool isLeaf() const;
    virtual QString getName() const;
    virtual QDateTime deadlineDelivery() const;
    virtual QDateTime deadlineCopywriters() const;
    virtual void setName(QString const & a_rName);
    virtual void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery);
    virtual void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters);

private:
    KotkaSource::STaskData m_sData;
};

#endif // CTASK_H
