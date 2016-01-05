#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>
#include <QMultiMap>
#include "chttpbrowsersync.h"
#include "commonddefs.h"

class CProjectManager;
class CClientsAndWritersDbModel;

class CRemoteDataStorage : public QObject
{
    Q_OBJECT
public:
    CRemoteDataStorage(QObject * a_pParent = 0);
    ~CRemoteDataStorage();

    void testMethod();
    void connectSignalsAndSlots(CProjectManager & a_rProjectMngr);
    void connectSignalsAndSlots(CClientsAndWritersDbModel & a_rContactBook);

    static const QString s_strLocalDataFileName;

signals:
    void loadFullContactListSignal(QList<KotkaSource::SContactData> const &, bool);
    void loadFullPrjsHierarchySignal( QList<KotkaSource::SProjectData> const &
                                    , QList<KotkaSource::STaskData> const &
                                    , QList<KotkaSource::SSourceData> const &
                                    );

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

private:
    void sendNewDataToServer(QJsonObject &a_rJsonObject);
    void sendRemoveDataReqToServer(QJsonObject const & a_crJsonObject);
    void sendUpdateDataReqToServer(QJsonObject const & a_crJsonObject);

    void sendGetProjectsDataReq(QString & a_strOutFileName);
    void sendGetTasksDataReq(QString & a_strOutFileName);
    void sendGetTaskObjectsDataReq(QString & a_strOutFileName);
    void sendGetContactsDataReq(QString & a_strOutFileName);
    void sendGetAllDataReq(QString & a_strOutFileName);

    bool importJsonDataFromFile(QString const & a_strFileName, QJsonDocument & a_rJsonDoc);
    void importFullContactsList(QJsonObject &a_rDataJsonObj);
    void importFullPrjHierarchy(QJsonObject & a_rDataJsonObj);
    void importFullProjecsData(QJsonObject & a_rDataJsonObj, QList<KotkaSource::SProjectData> & a_rProjectDataList);
    void importFullTasksData(QJsonObject & a_rDataJsonObj, QList<KotkaSource::STaskData> & a_rTaskDataList);
    void importFullTaskObjectsData(QJsonObject & a_rDataJsonObj, QMultiMap<QString, KotkaSource::STaskObjectData> & a_rTaskObjMap);

    void addLoginCredentials(QJsonObject &a_rJsonObj);

    QString getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const;
    KotkaSource::ETaskObjectType toTaskObjectType(QString a_strTypeName);

    CHttpBrowserSync m_oHttpBrowser;
    QString m_strAllDataLocalFileName;
};

#endif // CREMOTEDATASTORAGE_H
