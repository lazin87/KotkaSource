#ifndef CTASK_H
#define CTASK_H

#include "iproject.h"
//#include <QStandardItem>

#include "commonddefs.h"

class CTask : public IProject
{
public:
    explicit CTask(QString a_strName);
    explicit CTask(KotkaSource::STaskData const & a_rTaskData);

    ~CTask();

    // IProject interface
    virtual bool isLeaf() const;

private:
    KotkaSource::STaskData m_sData;
};

#endif // CTASK_H
