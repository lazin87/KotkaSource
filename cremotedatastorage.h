#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>
#include <QMultiMap>
#include "chttpbrowsersync.h"
#include "commonddefs.h"
#include <QJsonObject>

class CProjectManager;
class CContactsDbModel;

class CRemoteDataStorage : public QObject
{
    Q_OBJECT
public:
    enum EDataTransReqType
    {
        eDTR_newRecord = 0,
        eDTR_updateRecord,
        eDTR_removeRecord,
        eDTR_getAllData,
        eDTR_checkUpdates,

        eDTR_COUNT
    };

    enum EOperationType
    {
        eOpT_Invalid = -1,
        eOpT_Add = 0,
        eOpT_Mod,
        eOpT_Rem,

        eOpT_COUNT
    };

    static const QString aTARGET_URLs[eDTR_COUNT];
    static const QString aOUT_FILES_NAMES[eDTR_COUNT];
    static const QString aRECORD_TYPE_NAMES[KotkaSource::eRT_COUNT];
    static const QString aOPERATION_TYPE_NAMES[eOpT_COUNT];

    static const int iINVALID_VERSION = -1;
    CRemoteDataStorage(QObject * a_pParent = 0);
    ~CRemoteDataStorage();

    void testMethod();
    void connectSignalsAndSlots(CProjectManager & a_rProjectMngr);
    void connectSignalsAndSlots(CContactsDbModel & a_rContactBook);

    static const QString s_strLocalDataFileName;

signals:
    void loadFullContactListSignal(QList<KotkaSource::SContactData> const &, bool);
    void loadFullPrjsHierarchySignal( QList<KotkaSource::SProjectData> const &
                                    , QList<KotkaSource::STaskData> const &
                                    , QList<KotkaSource::SSourceData> const &
                                    );
    void loadNewRecord(KotkaSource::ERecordType eRecordType, QVariant const & rRecordData);

public slots:
    void storeTask(KotkaSource::STaskData const & a_crTaskData);
    void storeProject(KotkaSource::SProjectData const & a_crProjectData);
    void storeTaskObject(KotkaSource::STaskObjectData const & a_crTaskObjectData);
    void storeContact(KotkaSource::SContactData const & a_crContactData);

    void updateTask(KotkaSource::STaskData const & a_crTaskData);
    void updateProject(KotkaSource::SProjectData const & a_crProjectData);
    void updateTaskObject(KotkaSource::STaskObjectData const & a_crTaskObjectData);
    void updateContact(KotkaSource::SContactData const & a_crContactData);

    void removeTask(QString const & a_crName);
    void removeProject(QString const & a_crName);
    void removeTaskObject(QString const & a_crName);
    void removeContact(QString const & a_crName);

    void loadProjectsData(QList<KotkaSource::SProjectData> & a_rProject);
    bool downloadAllDataFromServer();

    bool checkForUpdates();
    bool processUpdateServResponse(QJsonObject & a_rMainJsonObj);

private:
    void fillInSProjectData(QJsonObject &a_rJsonPrjObj, KotkaSource::SProjectData &a_rPrjData);
    void fillInSTaskData(QJsonObject &a_rJsonTaskObj, KotkaSource::STaskData &a_rTaskData);
    void fillInSTaskObjectData(QJsonObject &a_rJsonTaskObj, KotkaSource::STaskObjectData &a_rTaskObj);
    void fillInSContactData(QJsonObject &a_rJsonContact, KotkaSource::SContactData &a_rContactData);

    bool importJsonDataFromFile(QString const & a_strFileName, QJsonDocument & a_rJsonDoc);
    void importFullContactsList(QJsonObject &a_rDataJsonObj);
    void importFullPrjHierarchy(QJsonObject & a_rDataJsonObj);
    void importFullProjecsData(QJsonObject & a_rDataJsonObj, QList<KotkaSource::SProjectData> & a_rProjectDataList);
    void importFullTasksData(QJsonObject & a_rDataJsonObj, QList<KotkaSource::STaskData> & a_rTaskDataList);
    void importFullTaskObjectsData(QJsonObject & a_rDataJsonObj, QMultiMap<QString, KotkaSource::STaskObjectData> & a_rTaskObjMap);
    bool readCurrentVersion(QJsonObject & a_rJsonMainObj);
    bool checkServerErrMsg(QJsonObject & a_rJsonMainObj);

    void addLoginCredentials(QJsonObject &a_rJsonObj);
    void processServerResponse(EDataTransReqType a_eDataReqType, QString const & a_rFileName);
    QString sendRequestToServer(EDataTransReqType a_eDataReqType, QJsonObject a_JsonReqObj = QJsonObject() );

    QString getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const;

    bool addNewRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject & a_rJsonDataObj);
    bool modRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject & a_rJsonDataObj);
    bool removeRecord(KotkaSource::ERecordType a_eRecordType, QJsonObject & a_rJsonDataObj);

    KotkaSource::ETaskObjectType toTaskObjectType(QString a_strTypeName);
    KotkaSource::ERecordType toRecordType(QString const & a_rName);
    EOperationType toOperationType(QString const & a_rName);

    CHttpBrowserSync m_oHttpBrowser;
    QString m_strAllDataLocalFileName;
    int m_iCurrentVersion;
};

#endif // CREMOTEDATASTORAGE_H
