#ifndef CXLSXCASTOSOURCEPARSER_H
#define CXLSXCASTOSOURCEPARSER_H

#include "isourceparsestrategy.h"

#include "xlsxdocument.h"

/** Simple Hello World!
       QXlsx::Document xlsx;
       xlsx.write("A1", "Hello Qt!");
       xlsx.saveAs("Test.xlsx");
 */

class CXlsxCastoSourceParser : public ISourceParseStrategy
{
public:
    CXlsxCastoSourceParser();
    ~CXlsxCastoSourceParser();

    // ISourceParseStrategy interface
    virtual bool getTaskDataList(QList<KotkaSource::STaskData> a_rTaskDataList, QIODevice * a_pDevice);
    virtual bool fillInSourceDoc(const KotkaSource::STaskData &a_crTaskData, const QTextStream &a_crTextStream);
};

#endif // CXLSXCASTOSOURCEPARSER_H
