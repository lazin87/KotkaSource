#include "cprojectbase.h"

CProjectBase::CProjectBase(QString a_strName, const IProject * a_pProjectParent)
    : IProject(a_strName, a_pProjectParent)
{
    qWarning("CProjectBase::CProjectBase");
}

CProjectBase::~CProjectBase()
{
    qWarning("CProjectBase::~CProjectBase()");
}
