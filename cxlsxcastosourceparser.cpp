#include "cxlsxcastosourceparser.h"

#include "QDebug"

CXlsxCastoSourceParser::CXlsxCastoSourceParser()
    : m_aiCOLUMNS_DESC{3, 1, 6, 7, 8, 9}
    , m_aiCOLUMNS_DATA{4, 5}
{

}

CXlsxCastoSourceParser::~CXlsxCastoSourceParser()
{

}



bool CXlsxCastoSourceParser::getTaskDataList(QList<KotkaSource::STaskData> a_rTaskDataList, QIODevice *a_pDevice)
{
    qDebug() << "CXlsxCastoSourceParser::getTaskDataList";

    QXlsx::Document oDoc(a_pDevice);

    for( int iRow = cFIRST_DATA_ROW
       ; (cMAX_DATA_ROW > iRow) && (false == isRowEmpty(iRow, oDoc) )
       ; ++iRow )
    {
        KotkaSource::STaskData taskData;

        setTaskId(taskData, iRow);
        setTaskDesc(taskData, iRow, oDoc);
        setTaskObjects(taskData, iRow, oDoc);

        a_rTaskDataList.append(taskData);
    }

    return true;
}

bool CXlsxCastoSourceParser::fillInSourceDoc(const KotkaSource::STaskData &a_crTaskData, const QTextStream &a_crTextStream)
{
    return false;
}

void CXlsxCastoSourceParser::setTaskId(KotkaSource::STaskData &a_rTaskData, int a_iRow)
{
    a_rTaskData.m_iId = a_iRow;
}

void CXlsxCastoSourceParser::setTaskDesc(KotkaSource::STaskData &a_rTaskData, int a_iRow, QXlsx::Document & a_rXlsxDoc)
{
    foreach(int iColumn, m_aiCOLUMNS_DESC)
    {
        a_rTaskData.m_strDesc += a_rXlsxDoc.read(cTITLE_ROW, iColumn).toString()
                + ": " + a_rXlsxDoc.read(a_iRow, iColumn).toString()
                + "\n";
    }
}

void CXlsxCastoSourceParser::setTaskObjects(KotkaSource::STaskData &a_rTaskData, int a_iRow, QXlsx::Document & a_rXlsxDoc)
{
    foreach(int iColumn, m_aiCOLUMNS_DATA)
    {
        KotkaSource::STaskObjectData taskObjectData;
        taskObjectData.m_iMinLength = 0;
        taskObjectData.m_iMaxLength = 0;
        taskObjectData.m_eType = KotkaSource::eTOT_Text;
        taskObjectData.m_strCurrentText = a_rXlsxDoc.read(a_iRow, iColumn).toString();
        taskObjectData.m_strTitle = a_rXlsxDoc.read(cTITLE_ROW, iColumn).toString();

        a_rTaskData.m_aTextFieldsList.append(taskObjectData);
    }
}

bool CXlsxCastoSourceParser::isRowEmpty(int a_iRow, QXlsx::Document &a_rXlsxDoc)
{
    return a_rXlsxDoc.read(a_iRow, cREQ_COLUMN).toString().isEmpty();
}
