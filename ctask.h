#ifndef CTASK_H
#define CTASK_H

#include "cproject.h"

class CTask : public CProject
{
public:
    CTask(QString a_strName, const CProject * a_pProjectParent);
    ~CTask();

    // CProject interface
    virtual bool isLeaf() const;
};

#endif // CTASK_H
