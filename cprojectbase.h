#ifndef CPROJECTBASE_H
#define CPROJECTBASE_H

#include "iproject.h"
#include <QList>
#include <QStandardItem>

class CProjectBase : public IProject
{
public:
    CProjectBase(QString a_strName, const IProject * a_pProjectParent = 0);
    ~CProjectBase();

    // IProject interface
    virtual bool addChild(IProject *a_pChild);
    virtual IProject *peekChild(int a_iIndex);
    virtual bool removeChild(int a_iIndex);
    virtual void removeAllChildren();
    virtual QStandardItem *getStandardItem();

    QVariant data(int role) const;

protected:
    QList<IProject* > m_pProjectChildrens;
    //QStandardItem m_oStandardItem;
};

#endif // CPROJECTBASE_H
