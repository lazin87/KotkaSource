#ifndef CSUBPROJECT_H
#define CSUBPROJECT_H

#include "cproject.h"

#include <QList>

class CSubProject : public CProject
{
public:
    CSubProject(QString a_strName, const CProject * a_pProjectParent);
    ~CSubProject();

private:
    QList<CProject* > m_pChildren;
};

#endif // CSUBPROJECT_H
