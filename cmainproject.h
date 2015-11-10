#ifndef CMAINPROJECT_H
#define CMAINPROJECT_H

#include "cprojectbase.h"

#include <QList>

class CMainProject : public CProjectBase
{
public:
    explicit CMainProject(QString a_strName);
    ~CMainProject();

    bool newSubproject(QString a_strName);
    bool removeSubproject(int a_iIndex);

};

#endif // CMAINPROJECT_H
