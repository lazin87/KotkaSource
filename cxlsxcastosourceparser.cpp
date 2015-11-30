#include "cxlsxcastosourceparser.h"

#include "QDebug"

CXlsxCastoSourceParser::CXlsxCastoSourceParser()
{

}

CXlsxCastoSourceParser::~CXlsxCastoSourceParser()
{

}



bool CXlsxCastoSourceParser::getTaskDataList(QList<KotkaSource::STaskData> a_rTaskDataList, QIODevice *a_pDevice)
{
    qDebug() << "CXlsxCastoSourceParser::getTaskDataList";
    QXlsx::Document oDoc(a_pDevice);

    QString strCell = "A1";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "D8";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "B5";
    qDebug() << strCell << " " << oDoc.read(strCell);
    return true;
}

bool CXlsxCastoSourceParser::fillInSourceDoc(const KotkaSource::STaskData &a_crTaskData, const QTextStream &a_crTextStream)
{
    return false;
}
