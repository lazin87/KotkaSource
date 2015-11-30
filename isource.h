#ifndef ISOURCE_H
#define ISOURCE_H

#include <QFile>
#include <QString>

#include "commonddefs.h"

class ISourceParseStrategy;

class ISource
{
public:
    explicit ISource(QString const & a_rFileName);
    ~ISource();

    void setStrategy(ISourceParseStrategy * a_pParseStrategy);
    ISourceParseStrategy * strategy() const;

    void setReadOnlyFlag(bool a_fIsReadOnly);
    bool readTaskData(QList<KotkaSource::STaskData> a_rOutTaskList);
    bool storeTaskData(KotkaSource::STaskData const & a_crTaskData);
    void setParentModelName(QString const & a_rParentModelName);
    QString getName() const;

private:
    ISourceParseStrategy * m_pParseStrategy;
    bool m_fIsReadOnly;
   // QFile m_oFile;
    QString m_strName;
    QString m_strParentModelName;
};

#endif // ISOURCE_H
