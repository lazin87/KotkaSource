#ifndef CSUBPROJECT_H
#define CSUBPROJECT_H

#include "cproject.h"

class CSubProject : public CProject
{
public:
    CSubProject(QString a_strName, const CProject * a_pProjectParent);
    ~CSubProject();
};

#endif // CSUBPROJECT_H
