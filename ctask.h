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
//    virtual bool addChild(IProject *a_pChild);
//    virtual IProject *peekChild(int a_iIndex);
//    virtual bool removeChild(int a_iIndex);
//    virtual void removeAllChildren();
    virtual QStandardItem *getStandardItem();
   // virtual QVariant data(int a_iRole) const;

protected:
};

#endif // CTASK_H
