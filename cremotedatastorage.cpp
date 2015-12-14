#include "cremotedatastorage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "cprojectmanager.h"

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
    QString strOutputFileName = "json_test.txt";

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
    m_oHttpBrowser.startProcessRequest(strOutputFileName);
}

void CRemoteDataStorage::connectSignalsAndSlots(CProjectManager &a_rProjectMngr)
{
    QObject::connect( &a_rProjectMngr, SIGNAL(projectWasCreated(KotkaSource::SProjectData) )
                    , this, SLOT(storeProject(KotkaSource::SProjectData) )
                    );
}

void CRemoteDataStorage::storeProject(const KotkaSource::SProjectData &a_crProjectData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectProjectData;

    oJsonObjectProjectData["name"] = a_crProjectData.m_strName;
    oJsonObjectProjectData["parent"] = a_crProjectData.m_strParentName;
    oJsonObjectProjectData["delivery"] = a_crProjectData.m_oDateTimeDelivery.toString(Qt::ISODate);
    oJsonObjectProjectData["wDeadline"] = a_crProjectData.m_oDateTimeWriterDeadline.toString(Qt::ISODate);
    oJsonObjectProjectData["client"] = a_crProjectData.m_strClientName;

    oJsonStoreMainObj["type"] = "project";
    oJsonStoreMainObj["data"] = oJsonObjectProjectData;

    sendNewDataToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::sendNewDataToServer(const QJsonObject &a_crJsonObject)
{
    QJsonDocument oJsonDoc;
    QString strOutputFileName = "jsonStoreOut.txt";
    oJsonDoc.setObject(a_crJsonObject);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/addRecord.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(strOutputFileName);
}

