#ifndef CMAINPROJECT_H
#define CMAINPROJECT_H

#include <QList>

#include "iproject.h"

class CMainProject : public IProject
{
public:
    explicit CMainProject(QString a_strName);
    ~CMainProject();

    bool newSubproject(QString a_strName);
    bool removeSubproject(int a_iIndex);

    // IProject interface
    virtual bool addChild(IProject *a_pChild);
    virtual IProject *peekChild(int a_iIndex);
    virtual bool removeChild(int a_iIndex);


private:
    QList<IProject* > m_SubprojectsPtrList;

};

#endif // CMAINPROJECT_H
