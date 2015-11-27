#ifndef ISOURCE_H
#define ISOURCE_H

#include <QFile>
#include <QString>

#include "commonddefs.h"

class ISourceTranslateStrategy;

class ISource
{
public:
    explicit ISource(QString const & a_rFileName);
    ~ISource();

    void setStrategy(ISourceTranslateStrategy * a_pTranslateStrategy);
    ISourceTranslateStrategy * strategy() const;

    void setReadOnlyFlag(bool a_fIsReadOnly);
    bool readTaskData(QList<KotkaSource::STaskData> a_rOutTaskList);
    bool storeTaskData(KotkaSource::STaskData const & a_crTaskData);
    QString getName() const;

private:
    ISourceTranslateStrategy * m_pTranslateStrategy;
    bool m_fIsReadOnly;
    QFile m_oFile;
    QString m_strName;
};

#endif // ISOURCE_H
