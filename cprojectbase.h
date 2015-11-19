#ifndef CPROJECTBASE_H
#define CPROJECTBASE_H

#include "iproject.h"
#include <QStandardItem>

class CProjectBase : public IProject
{
public:
    CProjectBase(QString a_strName);
    ~CProjectBase();
};

#endif // CPROJECTBASE_H
