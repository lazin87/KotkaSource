#ifndef CPROJECT_H
#define CPROJECT_H

#include <QString>
#include <QDateTime>
#include <QStandardItem>

#include "commonddefs.h"

class IProject : public QStandardItem
{
public:
    explicit IProject(QString a_strName);
    virtual ~IProject();

    virtual bool isLeaf() const;

    virtual QVariant data(int a_iRole) const;
    virtual void setData(const QVariant &a_value, int a_iRole);

    virtual QString getName() const = 0;
    virtual QString getParentName() const = 0;
    virtual QDateTime deadlineDelivery() const = 0;
    virtual QDateTime deadlineCopywriters() const = 0;
    virtual void setName(QString const & a_rName) = 0;
    virtual void setParentName(QString const & a_rParentName) = 0;
    virtual void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery) = 0;
    virtual void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters) = 0;

    virtual void fillInSourcesModel(QList<KotkaSource::SSourceData> const & a_rSourceList);
    virtual void parseSources();

//protected:
//    // PRZENIESC DO CPROJECTBASE!!!
//    KotkaSource::SProjectData m_sData;

    // TO DO dodac membera do przechowywania zrodel
};

#endif // CPROJECT_H
