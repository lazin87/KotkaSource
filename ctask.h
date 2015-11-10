#ifndef CTASK_H
#define CTASK_H

#include "iproject.h"

class CTask : public IProject
{
public:
    CTask(QString a_strName, const IProject * a_pProjectParent);
    ~CTask();

    // IProject interface
    virtual bool isLeaf() const;
    virtual bool addChild(IProject *a_pChild);
    virtual IProject *peekChild(int a_iIndex);
    virtual bool removeChild(int a_iIndex);
};

#endif // CTASK_H
