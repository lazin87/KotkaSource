#ifndef CXLSXCASTOSOURCEPARSER_H
#define CXLSXCASTOSOURCEPARSER_H

#include "isourceparsestrategy.h"

#include <QVector>

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

private:
    void setTaskId(KotkaSource::STaskData & a_rTaskData);
    void setTaskDesc(KotkaSource::STaskData & a_rTaskData);
    void setTaskObjects(KotkaSource::STaskData & a_rTaskData);

    QVector<const int> m_aiCOLUMNS_DESC;
    QVector<const int> m_aiCOLUMNS_DATA;
};

#endif // CXLSXCASTOSOURCEPARSER_H
