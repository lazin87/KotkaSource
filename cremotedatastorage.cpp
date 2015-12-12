#include "cremotedatastorage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

CRemoteDataStorage::CRemoteDataStorage(QObject *a_pParent)
    : QObject(a_pParent)
    , m_oHttpBrowser(this)
{

}

CRemoteDataStorage::~CRemoteDataStorage()
{

}

void CRemoteDataStorage::testMethod()
{
    QJsonDocument oJsonDoc;

    QJsonObject oJsonObject;
    oJsonObject["test1"] = "test1Value";
    oJsonObject["test2"] = "aącć";

    oJsonDoc.setObject(oJsonObject);

    qDebug() << "CRemoteDataStorage::testMethod() raw data:";
    qDebug() << oJsonDoc.toJson();
    qDebug() << "CRemoteDataStorage::testMethod() qstring data:";
    qDebug() << QString(oJsonDoc.toJson() );

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/json_test.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(QString("json_test.txt") );
}

