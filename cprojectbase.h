#ifndef CPROJECTBASE_H
#define CPROJECTBASE_H

#include "iproject.h"
#include <QStandardItem>

class CProjectBase : public IProject
{
public:
    CProjectBase(QString a_strName, const IProject * a_pProjectParent = 0);
    ~CProjectBase();
};

#endif // CPROJECTBASE_H
