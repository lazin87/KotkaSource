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
    // get ID/Name
    // get description
    // get fields name to fill in
    qDebug() << "CXlsxCastoSourceParser::getTaskDataList";
    QXlsx::Document oDoc(a_pDevice);

    QString strCell = "A1";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "C5";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "B5";
    qDebug() << strCell << " " << oDoc.read(strCell);
    return true;
}

bool CXlsxCastoSourceParser::fillInSourceDoc(const KotkaSource::STaskData &a_crTaskData, const QTextStream &a_crTextStream)
{
    return false;
}

void CXlsxCastoSourceParser::setTaskId(KotkaSource::STaskData &a_rTaskData)
{

}

void CXlsxCastoSourceParser::setTaskDesc(KotkaSource::STaskData &a_rTaskData)
{

}

void CXlsxCastoSourceParser::setTaskObjects(KotkaSource::STaskData &a_rTaskData)
{

}
