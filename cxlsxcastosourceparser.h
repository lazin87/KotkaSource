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
    enum
    {
        cTITLE_ROW = 1,
        cREQ_COLUMN = 1,
        cFIRST_DATA_ROW = 2,
        cMAX_DATA_ROW = 65000
    };

    CXlsxCastoSourceParser();
    ~CXlsxCastoSourceParser();

    // ISourceParseStrategy interface
    virtual bool getTaskDataList(QList<KotkaSource::STaskData> a_rTaskDataList, QIODevice * a_pDevice);
    virtual bool fillInSourceDoc(const KotkaSource::STaskData &a_crTaskData, const QTextStream &a_crTextStream);

private:
    void setTaskId(KotkaSource::STaskData & a_rTaskData, int a_iRow);
    void setTaskDesc(KotkaSource::STaskData & a_rTaskData, int a_iRow, QXlsx::Document &a_rXlsxDoc);
    void setTaskObjects(KotkaSource::STaskData & a_rTaskData, int a_iRow, QXlsx::Document &a_rXlsxDoc);
    bool isRowEmpty(int a_iRow, QXlsx::Document &a_rXlsxDoc);

    const QVector<int> m_aiCOLUMNS_DESC;
    const QVector<int> m_aiCOLUMNS_DATA;
};

#endif // CXLSXCASTOSOURCEPARSER_H
