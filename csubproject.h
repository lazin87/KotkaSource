#ifndef CSUBPROJECT_H
#define CSUBPROJECT_H

#include "iproject.h"

#include <QList>

class CSubProject : public IProject
{
public:
    CSubProject(QString a_strName, const IProject * a_pProjectParent);
    ~CSubProject();

    // IProject interface
    virtual bool addChild(IProject *a_pChild);
    virtual IProject *peekChild(int a_iIndex);
    virtual bool removeChild(int a_iIndex);

private:
    QList<IProject* > m_pChildren;


};

#endif // CSUBPROJECT_H
