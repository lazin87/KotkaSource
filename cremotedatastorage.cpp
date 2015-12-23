#include "cremotedatastorage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

#include "cprojectmanager.h"
#include "cclientsandwritersdbmodel.h"

const QString CRemoteDataStorage::s_strLocalDataFileName = "localData.json";

CRemoteDataStorage::CRemoteDataStorage(QObject *a_pParent)
    : QObject(a_pParent)
    , m_oHttpBrowser(this)
    , m_strAllDataLocalFileName(s_strLocalDataFileName)
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

    QObject::connect( &a_rProjectMngr, SIGNAL(taskWasCreated(KotkaSource::STaskData) )
                    , this, SLOT(storeTask(KotkaSource::STaskData) )
                      );
}

void CRemoteDataStorage::connectSignalsAndSlots(CClientsAndWritersDbModel &a_rContactBook)
{
    QObject::connect( &a_rContactBook, SIGNAL(contactWasCreated(KotkaSource::SContactData) )
                    , this, SLOT(storeContact(KotkaSource::SContactData) )
                    );
}

void CRemoteDataStorage::storeTask(const KotkaSource::STaskData &a_crTaskData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectTaskData;

    oJsonObjectTaskData["name"] = a_crTaskData.m_strName;
    oJsonObjectTaskData["parent"] = a_crTaskData.m_strParentName;
    oJsonObjectTaskData["desc"] = a_crTaskData.m_strDesc;
    oJsonObjectTaskData["writer"] = a_crTaskData.m_strWriterName;
    oJsonObjectTaskData["delivery"] = a_crTaskData.m_oDateTimeDelivery.toString(Qt::ISODate);
    oJsonObjectTaskData["wDeadline"] = a_crTaskData.m_oDateTimeWriterDeadline.toString(Qt::ISODate);

    oJsonStoreMainObj["type"] = "task";
    oJsonStoreMainObj["data"] = oJsonObjectTaskData;

    sendNewDataToServer(oJsonStoreMainObj);
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

void CRemoteDataStorage::storeTaskObject(const KotkaSource::STaskObjectData &a_crTaskObjectData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectTaskObjectData;

    oJsonObjectTaskObjectData["name"] = a_crTaskObjectData.m_strTitle;
    oJsonObjectTaskObjectData["parent"] = a_crTaskObjectData.m_strParentTaskName;
    oJsonObjectTaskObjectData["currentText"] = a_crTaskObjectData.m_strCurrentText;
    oJsonObjectTaskObjectData["typeName"] = getTaskObjectTypeName(a_crTaskObjectData.m_eType);
    oJsonObjectTaskObjectData["minLength"] = a_crTaskObjectData.m_iMinLength;
    oJsonObjectTaskObjectData["maxLength"] = a_crTaskObjectData.m_iMaxLength;

    oJsonStoreMainObj["type"] = "taskObject";
    oJsonStoreMainObj["data"] = oJsonObjectTaskObjectData;

    sendNewDataToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::storeContact(const KotkaSource::SContactData &a_crContactData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectContactData;

    oJsonObjectContactData["name"] = a_crContactData.m_strName;
    oJsonObjectContactData["email"] = a_crContactData.m_strEmail;
    oJsonObjectContactData["phone"] = a_crContactData.m_strPhone;
    oJsonObjectContactData["address"] = a_crContactData.m_strAddress;
    oJsonObjectContactData["isWriter"] = a_crContactData.m_fIsWriter;
    oJsonObjectContactData["isClient"] = a_crContactData.m_fIsClient;

    oJsonStoreMainObj["type"] = "contact";
    oJsonStoreMainObj["data"] = oJsonObjectContactData;

    sendNewDataToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::updateTask(const KotkaSource::STaskData &a_crTaskData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectTaskData;

    oJsonObjectTaskData["name"] = a_crTaskData.m_strName;
    oJsonObjectTaskData["parent"] = a_crTaskData.m_strParentName;
    oJsonObjectTaskData["desc"] = a_crTaskData.m_strDesc;
    oJsonObjectTaskData["writer"] = a_crTaskData.m_strWriterName;
    oJsonObjectTaskData["delivery"] = a_crTaskData.m_oDateTimeDelivery.toString(Qt::ISODate);
    oJsonObjectTaskData["wDeadline"] = a_crTaskData.m_oDateTimeWriterDeadline.toString(Qt::ISODate);

    oJsonStoreMainObj["type"] = "task";
    oJsonStoreMainObj["data"] = oJsonObjectTaskData;

    sendUpdateDataReqToServer(oJsonObjectTaskData);
}

void CRemoteDataStorage::updateProject(const KotkaSource::SProjectData &a_crProjectData)
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

    sendUpdateDataReqToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::updateTaskObject(const KotkaSource::STaskObjectData &a_crTaskObjectData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectTaskObjectData;

    oJsonObjectTaskObjectData["name"] = a_crTaskObjectData.m_strTitle;
    oJsonObjectTaskObjectData["parent"] = a_crTaskObjectData.m_strParentTaskName;
    oJsonObjectTaskObjectData["currentText"] = a_crTaskObjectData.m_strCurrentText;
    oJsonObjectTaskObjectData["typeName"] = getTaskObjectTypeName(a_crTaskObjectData.m_eType);
    oJsonObjectTaskObjectData["minLength"] = a_crTaskObjectData.m_iMinLength;
    oJsonObjectTaskObjectData["maxLength"] = a_crTaskObjectData.m_iMaxLength;

    oJsonStoreMainObj["type"] = "taskObject";
    oJsonStoreMainObj["data"] = oJsonObjectTaskObjectData;

    sendUpdateDataReqToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::updateContact(const KotkaSource::SContactData &a_crContactData)
{
    QJsonObject oJsonStoreMainObj;
    QJsonObject oJsonObjectContactData;

    oJsonObjectContactData["name"] = a_crContactData.m_strName;
    oJsonObjectContactData["email"] = a_crContactData.m_strEmail;
    oJsonObjectContactData["phone"] = a_crContactData.m_strPhone;
    oJsonObjectContactData["address"] = a_crContactData.m_strAddress;
    oJsonObjectContactData["isWriter"] = a_crContactData.m_fIsWriter;
    oJsonObjectContactData["isClient"] = a_crContactData.m_fIsClient;

    oJsonStoreMainObj["type"] = "contact";
    oJsonStoreMainObj["data"] = oJsonObjectContactData;

    sendUpdateDataReqToServer(oJsonStoreMainObj);
}

void CRemoteDataStorage::removeTask(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "task";
    oJsonMainObj["data"] = a_crName;

    sendRemoveDataReqToServer(oJsonMainObj);
}

void CRemoteDataStorage::removeProject(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "project";
    oJsonMainObj["data"] = a_crName;

    sendRemoveDataReqToServer(oJsonMainObj);
}

void CRemoteDataStorage::removeTaskObject(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "taskObject";
    oJsonMainObj["data"] = a_crName;

    sendRemoveDataReqToServer(oJsonMainObj);
}

void CRemoteDataStorage::removeContact(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "contact";
    oJsonMainObj["data"] = a_crName;

    sendRemoveDataReqToServer(oJsonMainObj);
}

void CRemoteDataStorage::loadProjectsData(QList<KotkaSource::SProjectData> &a_rProject)
{
    a_rProject.clear();

    QString strProjectsDataFile = "projetsData.json";
    sendGetProjectsDataReq(strProjectsDataFile);

    QFile dataFile(strProjectsDataFile);
    if(dataFile.open(QIODevice::ReadOnly) )
    {
        QByteArray storedData = dataFile.readAll();
        QJsonDocument jsonData(QJsonDocument::fromJson(storedData) );
    }
}

bool CRemoteDataStorage::downloadAllDataFromServer()
{
    bool fResult = false;

    return fResult;
}

void CRemoteDataStorage::sendNewDataToServer(QJsonObject &a_rJsonObject)
{
    QJsonDocument oJsonDoc;
    QString strOutputFileName = "jsonStoreOut.txt";
    addLoginCredentials(a_rJsonObject);
    oJsonDoc.setObject(a_rJsonObject);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/addRecord.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(strOutputFileName);
}

void CRemoteDataStorage::sendRemoveDataReqToServer(const QJsonObject &a_crJsonObject)
{
    QJsonDocument oJsonDoc;
    QString strOutputFileName = "jsonRemoveOut.txt";
    oJsonDoc.setObject(a_crJsonObject);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/removeRecord.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(strOutputFileName);
}

void CRemoteDataStorage::sendUpdateDataReqToServer(const QJsonObject &a_crJsonObject)
{
    QJsonDocument oJsonDoc;
    QString strOutputFileName = "jsonUpdateOut.txt";
    oJsonDoc.setObject(a_crJsonObject);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/updateRecord.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(strOutputFileName);
}

void CRemoteDataStorage::sendGetProjectsDataReq(QString & a_strOutFileName)
{
    QJsonDocument oJsonDoc;
    QJsonObject oJsonObj;
    addLoginCredentials(oJsonObj);
    oJsonDoc.setObject(oJsonObj);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/getProjects.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(a_strOutFileName);
}

void CRemoteDataStorage::sendGetAllDataReq(QString &a_strOutFileName)
{
    QJsonDocument oJsonDoc;
    QJsonObject oJsonObj;
    addLoginCredentials(oJsonObj);
    oJsonDoc.setObject(oJsonObj);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl("http://procner-michelin.com/CopyMngr/ctrl/getAllData.php");
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    m_oHttpBrowser.startProcessRequest(a_strOutFileName);
}

void CRemoteDataStorage::addLoginCredentials(QJsonObject &a_rJsonObj)
{
    a_rJsonObj["login"] = "Misiek";
    a_rJsonObj["pwd"] = "qwert";
}

QString CRemoteDataStorage::getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const
{
    return QString( ( (KotkaSource::eTOT_Text == a_eTaskObjectType) ? "Text" : "File") );
}

