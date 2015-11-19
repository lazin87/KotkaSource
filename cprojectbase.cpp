#include "cprojectbase.h"

CProjectBase::CProjectBase(QString a_strName)
    : IProject(a_strName)
{
    qWarning("CProjectBase::CProjectBase");
}

CProjectBase::~CProjectBase()
{
    qWarning("CProjectBase::~CProjectBase()");
}
