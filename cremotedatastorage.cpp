#include "cremotedatastorage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

    QObject::connect( this, SIGNAL(loadFullPrjsHierarchySignal( QList<KotkaSource::SProjectData>
                                                              , QList<KotkaSource::STaskData>
                                                              , QList<KotkaSource::SSourceData>) )
                    , &a_rProjectMngr, SLOT(loadProjectsModel( QList<KotkaSource::SProjectData>
                                                             , QList<KotkaSource::STaskData>
                                                             , QList<KotkaSource::SSourceData>) )
                    );
}

void CRemoteDataStorage::connectSignalsAndSlots(CClientsAndWritersDbModel &a_rContactBook)
{
    QObject::connect( &a_rContactBook, SIGNAL(contactWasCreated(KotkaSource::SContactData) )
                    , this, SLOT(storeContact(KotkaSource::SContactData) )
                    );

    QObject::connect( this, SIGNAL(loadFullContactListSignal(QList<KotkaSource::SContactData>,bool) )
                    , &a_rContactBook, SLOT(addNewContactSlot(QList<KotkaSource::SContactData>,bool) )
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

    QString strAllDataFileName = "allData.json";
    sendGetAllDataReq(strAllDataFileName);

    QJsonDocument oJsonDoc;
    fResult = importJsonDataFromFile(strAllDataFileName, oJsonDoc);

    if(fResult)
    {
        QJsonObject jsonMainObj = oJsonDoc.object();
        QJsonObject jsonDataObj = jsonMainObj["data"].toObject();

        importFullContactsList(jsonDataObj);
        importFullPrjHierarchy(jsonDataObj);
    }

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

bool CRemoteDataStorage::importJsonDataFromFile(const QString &a_strFileName, QJsonDocument &a_rJsonDoc)
{
    bool fResult = false;

    QFile dataFile(a_strFileName);
    if(dataFile.open(QIODevice::ReadOnly) )
    {
        QByteArray storedData = dataFile.readAll();
        dataFile.close();
        a_rJsonDoc = QJsonDocument::fromJson(storedData);

        fResult = true;
    }
    else
    {
        qWarning() << "CRemoteDataStorage::importJsonDataFromFile: can not open data file: " << a_strFileName;
    }

    return fResult;
}

void CRemoteDataStorage::importFullContactsList(QJsonObject &a_rDataJsonObj)
{
    QList<KotkaSource::SContactData> aContactDataList;
    QJsonArray jsonContactArray = a_rDataJsonObj["contacts"].toArray();

    for(int iIndex = 0; jsonContactArray.size() > iIndex; ++iIndex)
    {
        QJsonObject jsonContact = jsonContactArray[iIndex].toObject();
        KotkaSource::SContactData oContactData;

        oContactData.m_strName = jsonContact["name"].toString();
        oContactData.m_strEmail = jsonContact["email"].toString();
        oContactData.m_strPhone = jsonContact["phone"].toString();
        oContactData.m_strAddress = jsonContact["address"].toString();
        oContactData.m_fIsClient = jsonContact["isClient"].toString() == "1";
        oContactData.m_fIsWriter = jsonContact["isWriter"].toString() == "1";

        aContactDataList.append(oContactData);
    }

    emit loadFullContactListSignal(aContactDataList, true);
}

void CRemoteDataStorage::importFullPrjHierarchy(QJsonObject &a_rDataJsonObj)
{
    QList<KotkaSource::SProjectData> oPrjData;
    QList<KotkaSource::STaskData> oTaskData;
    QList<KotkaSource::SSourceData> oSourcesData;

    importFullProjecsData(a_rDataJsonObj, oPrjData);
    importFullTasksData(a_rDataJsonObj, oTaskData);

    emit loadFullPrjsHierarchySignal(oPrjData, oTaskData, oSourcesData);
}

void CRemoteDataStorage::importFullProjecsData(QJsonObject &a_rDataJsonObj, QList<KotkaSource::SProjectData> &a_rProjectDataList)
{
    QJsonArray jsonPrjArray = a_rDataJsonObj["projects"].toArray();

    for(int i = 0; jsonPrjArray.size() > i; ++i)
    {
        QJsonObject jsonPrjObj = jsonPrjArray[i].toObject();
        KotkaSource::SProjectData oPrjData;

        oPrjData.m_strName = jsonPrjObj["name"].toString();
        oPrjData.m_oDateTimeDelivery = QDateTime::fromString(jsonPrjObj["delivery"].toString() , Qt::ISODate);
        oPrjData.m_oDateTimeWriterDeadline = QDateTime::fromString(jsonPrjObj["wDeadline"].toString() , Qt::ISODate);
        oPrjData.m_strParentName = jsonPrjObj["parent"].toString();
        oPrjData.m_strClientName = jsonPrjObj["client"].toString();
        oPrjData.m_pClient = 0;

        a_rProjectDataList.append(oPrjData);
    }
}

void CRemoteDataStorage::importFullTasksData(QJsonObject &a_rDataJsonObj, QList<KotkaSource::STaskData> &a_rTaskDataList)
{
    QMultiMap<QString, KotkaSource::STaskObjectData> oTaskObjMap;
    importFullTaskObjectsData(a_rDataJsonObj, oTaskObjMap);

    QJsonArray jsonTasksArray = a_rDataJsonObj["projects"].toArray();

    for(int i = 0; jsonTasksArray.size() > i; ++i)
    {
        KotkaSource::STaskData taskData;
        QJsonObject jsonTaskObj = jsonTasksArray[i].toObject();

        taskData.m_strName = jsonTaskObj["name"].toString();
        taskData.m_strDesc = jsonTaskObj["desc"].toString();
        taskData.m_strWriterName = jsonTaskObj["writer"].toString();
        taskData.m_oDateTimeDelivery = QDateTime::fromString(jsonTaskObj["delivery"].toString() , Qt::ISODate);
        taskData.m_oDateTimeWriterDeadline =  QDateTime::fromString(jsonTaskObj["wDeadline"].toString() , Qt::ISODate);
        taskData.m_strParentName = jsonTaskObj["parent"].toString();
        taskData.m_aTextFieldsList = oTaskObjMap.values(taskData.m_strName);

        a_rTaskDataList.append(taskData);
    }
}

void CRemoteDataStorage::importFullTaskObjectsData(QJsonObject &a_rDataJsonObj, QMultiMap<QString, KotkaSource::STaskObjectData> &a_rTaskObjMap)
{
    QJsonArray jsonTaskObjsArray = a_rDataJsonObj["taskObjects"].toArray();

    for(int i = 0; jsonTaskObjsArray.size() > i; ++i)
    {
        KotkaSource::STaskObjectData oTaskObj;
        QJsonObject jsonTaskObj = jsonTaskObjsArray[i].toObject();

        oTaskObj.m_strTitle = jsonTaskObj["name"].toString();
        oTaskObj.m_strCurrentText = jsonTaskObj["currentText"].toString();
        oTaskObj.m_iMinLength = jsonTaskObj["minLength"].toString().toInt();
        oTaskObj.m_iMaxLength = jsonTaskObj["maxLength"].toString().toInt();
        oTaskObj.m_eType = toTaskObjectType(jsonTaskObj["typeName"].toString() );
        oTaskObj.m_strParentTaskName = jsonTaskObj["parent"].toString();

        a_rTaskObjMap.insert(oTaskObj.m_strParentTaskName, oTaskObj);
    }
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

KotkaSource::ETaskObjectType CRemoteDataStorage::toTaskObjectType(QString a_strTypeName)
{
    KotkaSource::ETaskObjectType eType = KotkaSource::eTOT_Invalid;

    if(a_strTypeName == "Text")
    {
        eType = KotkaSource::eTOT_Text;
    }
    else if(a_strTypeName == "File")
    {
        eType = KotkaSource::eTOT_File;
    }

    return eType;
}

