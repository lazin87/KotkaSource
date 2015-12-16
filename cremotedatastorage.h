#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>
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

private:
    void sendNewDataToServer(QJsonObject const & a_crJsonObject);
    QString getTaskObjectTypeName(KotkaSource::ETaskObjectType a_eTaskObjectType) const;

    CHttpBrowserSync m_oHttpBrowser;
};

#endif // CREMOTEDATASTORAGE_H
