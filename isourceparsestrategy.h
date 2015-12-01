#ifndef ISOURCETRANSLATESTRATEGY_H
#define ISOURCETRANSLATESTRATEGY_H

#include <QList>
#include <QTextStream>

#include "commonddefs.h"

class ISourceParseStrategy
{
public:
    ISourceParseStrategy();
    ~ISourceParseStrategy();

    virtual bool getTaskDataList(QList<KotkaSource::STaskData> & a_rTaskDataList, QIODevice * device) = 0;
    virtual bool fillInSourceDoc(KotkaSource::STaskData const & a_crTaskData, QTextStream const & a_crTextStream) = 0;
};

#endif // ISOURCETRANSLATESTRATEGY_H
