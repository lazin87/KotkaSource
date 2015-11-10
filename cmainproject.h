#ifndef CMAINPROJECT_H
#define CMAINPROJECT_H

#include <QList>

#include "cproject.h"

class CMainProject : public CProject
{
public:
    explicit CMainProject(QString a_strName);
    ~CMainProject();

    bool newSubproject(QString a_strName);
    bool removeSubproject(int a_iIndex);

private:
    QList<CProject* > m_SubprojectsPtrList;
};

#endif // CMAINPROJECT_H
