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

private:
    void sendNewDataToServer(QJsonObject const & a_crJsonObject);
    void sendRemoveDataReqToServer(QJsonObject const & a_crJsonObject);
    void sendUpdateDataReqToServer(QJsonObject const & a_crJsonObject);

    void sendGetProjectsDataReq(QString & a_strOutFileName);
    void sendGetTasksDataReq(QString & a_strOutFileName);
    void sendGetTaskObjectsDataReq(QString & a_strOutFileName);
    void sendGetContactsDataReq(QString & a_strOutFileName);

    void addLoginCredentials(QJsonDocument & a_rJsonDoc);

    QString getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const;

    CHttpBrowserSync m_oHttpBrowser;
};

#endif // CREMOTEDATASTORAGE_H
