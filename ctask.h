#ifndef CTASK_H
#define CTASK_H

#include "iproject.h"
#include <QStandardItem>

class CTask : public IProject
{
public:
    CTask(QString a_strName, const IProject * a_pProjectParent);
    ~CTask();

    // IProject interface
    virtual bool isLeaf() const;
};

#endif // CTASK_H
