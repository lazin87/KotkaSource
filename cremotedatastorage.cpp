#include "cremotedatastorage.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

#include "cprojectmanager.h"
#include "CContactsDbModel.h"

const QString CRemoteDataStorage::s_strLocalDataFileName = "localData.json";

const QString CRemoteDataStorage::aTARGET_URLs[eDTR_COUNT] = {
    "http://procner-michelin.com/CopyMngr/ctrl/addRecord.php",
    "http://procner-michelin.com/CopyMngr/ctrl/updateRecord.php",
    "http://procner-michelin.com/CopyMngr/ctrl/removeRecord.php",
    "http://procner-michelin.com/CopyMngr/ctrl/getAllData.php",
    "http://procner-michelin.com/CopyMngr/ctrl/checkUpdates.php"
};

const QString CRemoteDataStorage::aOUT_FILES_NAMES[eDTR_COUNT] = {
    "newRecordOut.json",
    "updateRecordOut.json",
    "removeRecordOut.json",
    "getAllDataOut.json",
    "lastUpdates.json"
};

const QString CRemoteDataStorage::aRECORD_TYPE_NAMES[KotkaSource::eRT_COUNT] = {
    "project",
    "task",
    "taskObject",
    "contact"
};

const QString CRemoteDataStorage::aOPERATION_TYPE_NAMES[eOpT_COUNT] = {
    "add",
    "mod",
    "rem"
};

CRemoteDataStorage::CRemoteDataStorage(QObject *a_pParent)
    : QObject(a_pParent)
    , m_oHttpBrowser()
    , m_strAllDataLocalFileName(s_strLocalDataFileName)
    , m_iCurrentVersion(iINVALID_VERSION)
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

    QObject::connect( &a_rProjectMngr, SIGNAL(dataUpdateSignal(KotkaSource::SProjectData, QString) )
                    , this, SLOT(update(KotkaSource::SProjectData, QString) )
                    );

    QObject::connect( &a_rProjectMngr, SIGNAL(taskWasCreated(KotkaSource::STaskData) )
                    , this, SLOT(storeTask(KotkaSource::STaskData) )
                    );

    QObject::connect( &a_rProjectMngr, SIGNAL(dataUpdateSignal(KotkaSource::STaskData, QString) )
                    , this, SLOT(update(KotkaSource::STaskData, QString) )
                    );

    QObject::connect( this, SIGNAL(loadFullPrjsHierarchySignal( QList<KotkaSource::SProjectData>
                                                              , QList<KotkaSource::STaskData>
                                                              , QList<KotkaSource::SSourceData>) )
                    , &a_rProjectMngr, SLOT(loadProjectsModel( QList<KotkaSource::SProjectData>
                                                             , QList<KotkaSource::STaskData>
                                                             , QList<KotkaSource::SSourceData>) )
                    );
}

void CRemoteDataStorage::connectSignalsAndSlots(CContactsDbModel &a_rContactBook)
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

    fillInJsonData(oJsonStoreMainObj, a_crTaskData);

    QString outFileName = sendRequestToServer(eDTR_newRecord, oJsonStoreMainObj);
    processServerResponse(eDTR_newRecord, outFileName);

}

void CRemoteDataStorage::storeProject(const KotkaSource::SProjectData &a_crProjectData)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crProjectData);

    QString outFileName = sendRequestToServer(eDTR_newRecord, oJsonStoreMainObj);
    processServerResponse(eDTR_newRecord, outFileName);
}

void CRemoteDataStorage::storeTaskObject(const KotkaSource::STaskObjectData &a_crTaskObjectData)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crTaskObjectData);

    QString outFileName = sendRequestToServer(eDTR_newRecord, oJsonStoreMainObj);
    processServerResponse(eDTR_newRecord, outFileName);
}

void CRemoteDataStorage::storeContact(const KotkaSource::SContactData &a_crContactData)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crContactData);

    QString outFileName = sendRequestToServer(eDTR_newRecord, oJsonStoreMainObj);
    processServerResponse(eDTR_newRecord, outFileName);
}

void CRemoteDataStorage::update(const KotkaSource::STaskData &a_crTaskData, QString const & a_crOldName)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crTaskData);
    oJsonStoreMainObj["oldName"] = a_crOldName;

    sendRequestToServer(eDTR_updateRecord, oJsonStoreMainObj);
}

void CRemoteDataStorage::update(const KotkaSource::SProjectData &a_crProjectData, QString const & a_crOldName)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crProjectData);
    oJsonStoreMainObj["oldName"] = a_crOldName;

    sendRequestToServer(eDTR_updateRecord, oJsonStoreMainObj);
}

void CRemoteDataStorage::update(const KotkaSource::STaskObjectData &a_crTaskObjectData)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crTaskObjectData);
    sendRequestToServer(eDTR_updateRecord, oJsonStoreMainObj);
}

void CRemoteDataStorage::update(const KotkaSource::SContactData &a_crContactData)
{
    QJsonObject oJsonStoreMainObj;

    fillInJsonData(oJsonStoreMainObj, a_crContactData);
    sendRequestToServer(eDTR_updateRecord, oJsonStoreMainObj);
}

void CRemoteDataStorage::removeTask(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "task";
    oJsonMainObj["data"] = a_crName;

    sendRequestToServer(eDTR_removeRecord, oJsonMainObj);
}

void CRemoteDataStorage::removeProject(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "project";
    oJsonMainObj["data"] = a_crName;

    sendRequestToServer(eDTR_removeRecord, oJsonMainObj);
}

void CRemoteDataStorage::removeTaskObject(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "taskObject";
    oJsonMainObj["data"] = a_crName;

    sendRequestToServer(eDTR_removeRecord, oJsonMainObj);
}

void CRemoteDataStorage::removeContact(const QString &a_crName)
{
    QJsonObject oJsonMainObj;

    oJsonMainObj["type"] = "contact";
    oJsonMainObj["data"] = a_crName;

    sendRequestToServer(eDTR_removeRecord, oJsonMainObj);
}

void CRemoteDataStorage::loadProjectsData(QList<KotkaSource::SProjectData> &a_rProject)
{
//    a_rProject.clear();

//    QString strProjectsDataFile = "projetsData.json";
//    sendGetProjectsDataReq(strProjectsDataFile);

//    QFile dataFile(strProjectsDataFile);
//    if(dataFile.open(QIODevice::ReadOnly) )
//    {
//        QByteArray storedData = dataFile.readAll();
//        QJsonDocument jsonData(QJsonDocument::fromJson(storedData) );
//    }
}

bool CRemoteDataStorage::downloadAllDataFromServer()
{
    bool fResult = false;

    QJsonDocument oJsonDoc;
    QString strAllDataFileName = sendRequestToServer(eDTR_getAllData);
    fResult = !strAllDataFileName.isEmpty();//sendGetAllDataReq(strAllDataFileName);

    if(fResult)
    {
        fResult = importJsonDataFromFile(strAllDataFileName, oJsonDoc);
    }

    if(fResult)
    {
        QJsonObject jsonMainObj = oJsonDoc.object();
        QJsonObject jsonDataObj = jsonMainObj["data"].toObject();

        fResult = readCurrentVersion(jsonMainObj);

        if(fResult)
        {
            importFullContactsList(jsonDataObj);
            importFullPrjHierarchy(jsonDataObj);
        }
    }

    return fResult;
}

bool CRemoteDataStorage::checkForUpdates()
{
    qDebug() << "Check for updates";
    bool fResult = false;

    if(iINVALID_VERSION != m_iCurrentVersion)
    {
        QJsonObject oJsonMainObject;

        QString strOutFileName = sendRequestToServer(eDTR_checkUpdates, oJsonMainObject);
        processServerResponse(eDTR_checkUpdates, strOutFileName);
    }
    else
    {
        qWarning() << "CRemoteDataStorage::checkForUpdates(): Invalid version. Download db first";
    }

    return fResult;
}

bool CRemoteDataStorage::processUpdateServResponse(QJsonObject &a_rMainJsonObj)
{
    bool fResult  = false;
    QJsonArray jsonDataArray = a_rMainJsonObj["data"].toArray();
    for(int i = 0; jsonDataArray.size(); ++i)
    {
        QJsonObject jsonChangeDataObj = jsonDataArray[i].toObject();
        QJsonObject jsonObjMods = jsonChangeDataObj["mods"].toObject();
        KotkaSource::ERecordType eRecordType = toRecordType(jsonChangeDataObj["type"].toString() );
        EOperationType eOperationType = toOperationType(jsonChangeDataObj["action"].toString() );
        int iVersion = jsonChangeDataObj["id"].toString().toInt();

        switch(eOperationType)
        {
        case eOpT_Add:
        {
            fResult = addNewRecord(eRecordType, jsonObjMods);
        }
        break;

        case eOpT_Mod:
        {
            fResult = modRecord(eRecordType, jsonObjMods);
        }
        break;

        case eOpT_Rem:
        {
            fResult = removeRecord(eRecordType, jsonObjMods);
        }
        break;

        default:
        {
            fResult = false;
            qWarning() << "CRemoteDataStorage::processUpdateServResponse: unsupported record type: " << eOperationType;
        }
        }

    }

    return fResult;
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

void CRemoteDataStorage::fillInDataStruct(QJsonObject & a_rJsonContact, KotkaSource::SContactData & a_rContactData)
{
    a_rContactData.m_strName = a_rJsonContact["name"].toString();
    a_rContactData.m_strEmail = a_rJsonContact["email"].toString();
    a_rContactData.m_strPhone = a_rJsonContact["phone"].toString();
    a_rContactData.m_strAddress = a_rJsonContact["address"].toString();
    a_rContactData.m_fIsClient = a_rJsonContact["isClient"].toString() == "1";
    a_rContactData.m_fIsWriter = a_rJsonContact["isWriter"].toString() == "1";
}

void CRemoteDataStorage::fillInJsonData(QJsonObject &a_rMainJsonObj, const KotkaSource::SProjectData &a_crProjectData)
{
    QJsonObject oJsonObjectProjectData;

    if(noChange<QString>() != a_crProjectData.m_strName) oJsonObjectProjectData["name"] = a_crProjectData.m_strName;
    if(noChange<QString>() != a_crProjectData.m_strParentName) oJsonObjectProjectData["parent"] = a_crProjectData.m_strParentName;
    if(noChange<QDateTime>() != a_crProjectData.m_oDateTimeDelivery) oJsonObjectProjectData["delivery"] = a_crProjectData.m_oDateTimeDelivery.toString(Qt::ISODate);
    if(noChange<QDateTime>() != a_crProjectData.m_oDateTimeWriterDeadline) oJsonObjectProjectData["wDeadline"] = a_crProjectData.m_oDateTimeWriterDeadline.toString(Qt::ISODate);
    if(noChange<QString>() != a_crProjectData.m_strClientName) oJsonObjectProjectData["client"] = a_crProjectData.m_strClientName;

    a_rMainJsonObj["type"] = aRECORD_TYPE_NAMES[KotkaSource::eRT_Project];
    a_rMainJsonObj["data"] = oJsonObjectProjectData;
}

void CRemoteDataStorage::fillInJsonData(QJsonObject &a_rMainJsonObj, const KotkaSource::STaskData &a_crTaskData)
{
    QJsonObject oJsonObjectTaskData;

    if(noChange<QString>() != a_crTaskData.m_strName) oJsonObjectTaskData["name"] = a_crTaskData.m_strName;
    if(noChange<QString>() != a_crTaskData.m_strParentName) oJsonObjectTaskData["parent"] = a_crTaskData.m_strParentName;
    if(noChange<QString>() != a_crTaskData.m_strDesc) oJsonObjectTaskData["desc"] = a_crTaskData.m_strDesc;
    if(noChange<QString>() != a_crTaskData.m_strWriterName) oJsonObjectTaskData["writer"] = a_crTaskData.m_strWriterName;
    if(noChange<QDateTime>() != a_crTaskData.m_oDateTimeDelivery) oJsonObjectTaskData["delivery"] = a_crTaskData.m_oDateTimeDelivery.toString(Qt::ISODate);
    if(noChange<QDateTime>() != a_crTaskData.m_oDateTimeWriterDeadline) oJsonObjectTaskData["wDeadline"] = a_crTaskData.m_oDateTimeWriterDeadline.toString(Qt::ISODate);

    a_rMainJsonObj["type"] = aRECORD_TYPE_NAMES[KotkaSource::eRT_Task];
    a_rMainJsonObj["data"] = oJsonObjectTaskData;
}

void CRemoteDataStorage::fillInJsonData(QJsonObject &a_rMainJsonObj, const KotkaSource::STaskObjectData &a_crTaskObjectData)
{
    QJsonObject oJsonObjectTaskObjectData;

    oJsonObjectTaskObjectData["name"] = a_crTaskObjectData.m_strTitle;
    oJsonObjectTaskObjectData["parent"] = a_crTaskObjectData.m_strParentTaskName;
    oJsonObjectTaskObjectData["currentText"] = a_crTaskObjectData.m_strCurrentText;
    oJsonObjectTaskObjectData["typeName"] = getTaskObjectTypeName(a_crTaskObjectData.m_eType);
    oJsonObjectTaskObjectData["minLength"] = a_crTaskObjectData.m_iMinLength;
    oJsonObjectTaskObjectData["maxLength"] = a_crTaskObjectData.m_iMaxLength;

    a_rMainJsonObj["type"] = aRECORD_TYPE_NAMES[KotkaSource::eRT_TaskObj];
    a_rMainJsonObj["data"] = oJsonObjectTaskObjectData;
}

void CRemoteDataStorage::fillInJsonData(QJsonObject &a_rMainJsonObj, const KotkaSource::SContactData &a_crContactData)
{
    QJsonObject oJsonObjectContactData;

    oJsonObjectContactData["name"] = a_crContactData.m_strName;
    oJsonObjectContactData["email"] = a_crContactData.m_strEmail;
    oJsonObjectContactData["phone"] = a_crContactData.m_strPhone;
    oJsonObjectContactData["address"] = a_crContactData.m_strAddress;
    oJsonObjectContactData["isWriter"] = a_crContactData.m_fIsWriter;
    oJsonObjectContactData["isClient"] = a_crContactData.m_fIsClient;

    a_rMainJsonObj["type"] = aRECORD_TYPE_NAMES[KotkaSource::eRT_Contact];
    a_rMainJsonObj["data"] = oJsonObjectContactData;
}

void CRemoteDataStorage::importFullContactsList(QJsonObject &a_rDataJsonObj)
{
    QList<KotkaSource::SContactData> aContactDataList;
    QJsonArray jsonContactArray = a_rDataJsonObj["contacts"].toArray();

    for(int iIndex = 0; jsonContactArray.size() > iIndex; ++iIndex)
    {
        QJsonObject jsonContact = jsonContactArray[iIndex].toObject();
        KotkaSource::SContactData oContactData;

        fillInDataStruct(jsonContact, oContactData);

        aContactDataList.append(oContactData);
    }

    if(!aContactDataList.isEmpty() )
    {
        emit loadFullContactListSignal(aContactDataList, true);
    }
    else
    {
        qWarning() << "CRemoteDataStorage::importFullContactsList: list empty";
    }
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

void CRemoteDataStorage::fillInDataStruct(QJsonObject & a_rJsonPrjObj, KotkaSource::SProjectData & a_rPrjData)
{
    a_rPrjData.m_strName = a_rJsonPrjObj["name"].toString();
    a_rPrjData.m_oDateTimeDelivery = QDateTime::fromString(a_rJsonPrjObj["delivery"].toString() , Qt::ISODate);
    a_rPrjData.m_oDateTimeWriterDeadline = QDateTime::fromString(a_rJsonPrjObj["wDeadline"].toString() , Qt::ISODate);
    a_rPrjData.m_strParentName = a_rJsonPrjObj["parent"].toString();
    a_rPrjData.m_strClientName = a_rJsonPrjObj["client"].toString();
    a_rPrjData.m_pClient = 0;
}

void CRemoteDataStorage::importFullProjecsData(QJsonObject &a_rDataJsonObj, QList<KotkaSource::SProjectData> &a_rProjectDataList)
{
    QJsonArray jsonPrjArray = a_rDataJsonObj["projects"].toArray();

    for(int i = 0; jsonPrjArray.size() > i; ++i)
    {
        QJsonObject jsonPrjObj = jsonPrjArray[i].toObject();
        KotkaSource::SProjectData oPrjData;

        fillInDataStruct(jsonPrjObj, oPrjData);

        a_rProjectDataList.append(oPrjData);
    }
}

void CRemoteDataStorage::fillInDataStruct(QJsonObject & a_rJsonTaskObj, KotkaSource::STaskData & a_rTaskData)
{
    a_rTaskData.m_strName = a_rJsonTaskObj["name"].toString();
    a_rTaskData.m_strDesc = a_rJsonTaskObj["desc"].toString();
    a_rTaskData.m_strWriterName = a_rJsonTaskObj["writer"].toString();
    a_rTaskData.m_oDateTimeDelivery = QDateTime::fromString(a_rJsonTaskObj["delivery"].toString() , Qt::ISODate);
    a_rTaskData.m_oDateTimeWriterDeadline =  QDateTime::fromString(a_rJsonTaskObj["wDeadline"].toString() , Qt::ISODate);
    a_rTaskData.m_strParentName = a_rJsonTaskObj["parent"].toString();
}

void CRemoteDataStorage::importFullTasksData(QJsonObject &a_rDataJsonObj, QList<KotkaSource::STaskData> &a_rTaskDataList)
{
    QMultiMap<QString, KotkaSource::STaskObjectData> oTaskObjMap;
    importFullTaskObjectsData(a_rDataJsonObj, oTaskObjMap);

    QJsonArray jsonTasksArray = a_rDataJsonObj["tasks"].toArray();

    for(int i = 0; jsonTasksArray.size() > i; ++i)
    {
        KotkaSource::STaskData taskData;
        QJsonObject jsonTaskObj = jsonTasksArray[i].toObject();

        fillInDataStruct(jsonTaskObj, taskData);
        taskData.m_aTextFieldsList = oTaskObjMap.values(taskData.m_strName);

        a_rTaskDataList.append(taskData);
    }
}

void CRemoteDataStorage::fillInDataStruct(QJsonObject & a_rJsonTaskObj, KotkaSource::STaskObjectData & a_rTaskObj)
{
    a_rTaskObj.m_strTitle = a_rJsonTaskObj["name"].toString();
    a_rTaskObj.m_strCurrentText = a_rJsonTaskObj["currentText"].toString();
    a_rTaskObj.m_iMinLength = a_rJsonTaskObj["minLength"].toString().toInt();
    a_rTaskObj.m_iMaxLength = a_rJsonTaskObj["maxLength"].toString().toInt();
    a_rTaskObj.m_eType = toTaskObjectType(a_rJsonTaskObj["typeName"].toString() );
    a_rTaskObj.m_strParentTaskName = a_rJsonTaskObj["parent"].toString();
}

void CRemoteDataStorage::importFullTaskObjectsData(QJsonObject &a_rDataJsonObj, QMultiMap<QString, KotkaSource::STaskObjectData> &a_rTaskObjMap)
{
    QJsonArray jsonTaskObjsArray = a_rDataJsonObj["taskObjects"].toArray();

    for(int i = 0; jsonTaskObjsArray.size() > i; ++i)
    {
        KotkaSource::STaskObjectData oTaskObj;
        QJsonObject jsonTaskObj = jsonTaskObjsArray[i].toObject();

        fillInDataStruct(jsonTaskObj, oTaskObj);

        a_rTaskObjMap.insert(oTaskObj.m_strParentTaskName, oTaskObj);
    }
}

bool CRemoteDataStorage::readCurrentVersion(QJsonObject &a_rJsonMainObj)
{
    QString strReadedVersion = a_rJsonMainObj["ver"].toString();

    bool fResult = false;
    int iTempVer = strReadedVersion.toInt(&fResult);

    m_iCurrentVersion = fResult ? iTempVer : iINVALID_VERSION;

    qDebug() << "CRemoteDataStorage::readCurrentVersion: ver: " << m_iCurrentVersion
             << " result: " << fResult;

    return fResult;
}

bool CRemoteDataStorage::checkServerErrMsg(QJsonObject &a_rJsonMainObj)
{
    QString errMsg = a_rJsonMainObj["error"].toString();
    bool fResult = errMsg.isEmpty();

    if(fResult)
    {
        qDebug() << "CRemoteDataStorage::checkServerErrMsg: no errors";
    }
    else
    {
        qWarning() << "CRemoteDataStorage::checkServerErrMsg: " << errMsg;
    }

    return fResult;
}



void CRemoteDataStorage::addLoginCredentials(QJsonObject &a_rJsonObj)
{
    a_rJsonObj["login"] = "Misiek";
    a_rJsonObj["pwd"] = "qwert";
}

void CRemoteDataStorage::processServerResponse(CRemoteDataStorage::EDataTransReqType a_eDataReqType, const QString &a_rFileName)
{
    if(!a_rFileName.isEmpty() )
    {
        QJsonDocument oJsonDoc;
        bool fResult = importJsonDataFromFile(a_rFileName, oJsonDoc);
        QJsonObject jsonMainObj = fResult ? oJsonDoc.object() : QJsonObject() ;
        fResult = fResult ? checkServerErrMsg(jsonMainObj) : fResult;

        fResult = fResult ? readCurrentVersion(jsonMainObj) : fResult;
    }
    else
    {
        qWarning() << "CRemoteDataStorage::processServerResponse: out file name is empty";
    }
}

QString CRemoteDataStorage::sendRequestToServer(EDataTransReqType a_eDataReqType, QJsonObject a_JsonReqObj)
{
    QString strOutFileName = aOUT_FILES_NAMES[a_eDataReqType];

    QJsonDocument oJsonDoc;
    a_JsonReqObj["curVer"] = m_iCurrentVersion;
    addLoginCredentials(a_JsonReqObj);

    oJsonDoc.setObject(a_JsonReqObj);

    m_oHttpBrowser.setEHttpReq(CHttpBrowserSync::eHttpReqJson);
    m_oHttpBrowser.setUrl(aTARGET_URLs[a_eDataReqType] );
    m_oHttpBrowser.setDataToSend(oJsonDoc.toJson() );
    bool fResult = m_oHttpBrowser.startProcessRequest(strOutFileName);

    strOutFileName = fResult ? strOutFileName : "";

    return strOutFileName;
}

QString CRemoteDataStorage::getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const
{
    return QString( ( (KotkaSource::eTOT_Text == a_eTaskObjectType) ? "Text" : "File") );
}

bool CRemoteDataStorage::addNewRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject &a_rJsonDataObj)
{
    bool fResult = true;
    QVariant recordData;

    switch(a_eRecordType)
    {
    case KotkaSource::eRT_Project:
    {
        KotkaSource::SProjectData newPrjData;
        fillInDataStruct(a_rJsonDataObj, newPrjData);
        recordData = QVariant::fromValue(newPrjData);
    }
    break;

    case KotkaSource::eRT_Task:
    {
        KotkaSource::STaskData oNewTaskData;
        fillInDataStruct(a_rJsonDataObj, oNewTaskData);
        recordData = QVariant::fromValue(oNewTaskData);
    }
    break;

    case KotkaSource::eRT_TaskObj:
    {
        KotkaSource::STaskObjectData oNewTaskObj;
        fillInDataStruct(a_rJsonDataObj, oNewTaskObj);
        recordData = QVariant::fromValue(oNewTaskObj);
    }
    break;

    case KotkaSource::eRT_Contact:
    {
        KotkaSource::SContactData oNewContactData;
        fillInDataStruct(a_rJsonDataObj, oNewContactData);
        recordData = QVariant::fromValue(oNewContactData);
    }
    break;

    default:
        fResult = false;
        qWarning() << "CRemoteDataStorage::addNewRecord: unsupported record type" << a_eRecordType;
    }

    if(fResult)
    {
        emit loadNewRecord(a_eRecordType, recordData);
    }

    return fResult;
}

bool CRemoteDataStorage::modRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject &a_rJsonDataObj)
{
    bool fResult = false;

    return fResult;
}

bool CRemoteDataStorage::removeRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject &a_rJsonDataObj)
{
    bool fResult = false;

    return fResult;
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

KotkaSource::ERecordType CRemoteDataStorage::toRecordType(const QString &a_rName)
{
    QString const * pEqualElement = 0;
    KotkaSource::ERecordType eRecType = KotkaSource::eRT_Invalid;
    pEqualElement = std::find(aRECORD_TYPE_NAMES, aRECORD_TYPE_NAMES + KotkaSource::eRT_COUNT, a_rName);

    if(pEqualElement == (aRECORD_TYPE_NAMES + KotkaSource::eRT_COUNT) )
    {
        qWarning() << "CRemoteDataStorage::toRecordType: invalid record type";
    }
    else
    {
        eRecType = static_cast<KotkaSource::ERecordType>(pEqualElement - aRECORD_TYPE_NAMES);
    }

    return eRecType;
}
CRemoteDataStorage::EOperationType CRemoteDataStorage::toOperationType(QString const & a_rName)
{
    EOperationType eRetOpType = eOpT_Invalid;
    QString const * pEqualElement = 0;

    pEqualElement = std::find(aOPERATION_TYPE_NAMES, aOPERATION_TYPE_NAMES + eOpT_COUNT, a_rName);
    if(pEqualElement == (aOPERATION_TYPE_NAMES + eOpT_COUNT) )
    {
        qWarning() << "RemoteDataStorage::toOperationType: invalid record type";
    }
    else
    {
        eRetOpType = static_cast<EOperationType>(pEqualElement - aOPERATION_TYPE_NAMES);
    }

    return eRetOpType;
}

