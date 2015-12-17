#ifndef CPROJECTBASE_H
#define CPROJECTBASE_H

#include "iproject.h"
#include <QStandardItem>

#include "csourcesmodel.h"

class CProjectBase : public IProject
{
public:
    CProjectBase(QString a_strName);
    CProjectBase(KotkaSource::SProjectData const & a_crProjectData);
    ~CProjectBase();

    virtual QVariant data(int a_iRole) const;
    virtual void setData(const QVariant &a_value, int a_iRole);

    virtual QString getName() const;
    virtual QString getParentName() const;
    virtual QDateTime deadlineDelivery() const;
    virtual QDateTime deadlineCopywriters() const;
    virtual void setName(QString const & a_rName);
    virtual void setParentName(QString const & a_rParentName);
    virtual void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery);
    virtual void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters);

    virtual void fillInSourcesModel(QList<KotkaSource::SSourceData> const & a_rSourceList);
    virtual void parseSources();

private:
    KotkaSource::SProjectData m_sData;
    CSourcesModel m_oSourceModel;
};

#endif // CPROJECTBASE_H
