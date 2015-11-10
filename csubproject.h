#ifndef CSUBPROJECT_H
#define CSUBPROJECT_H

#include "cprojectbase.h"

#include <QList>

class CSubProject : public CProjectBase
{
public:
    CSubProject(QString a_strName, const IProject * a_pProjectParent);
    ~CSubProject();

};

#endif // CSUBPROJECT_H
