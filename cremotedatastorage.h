#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>
#include "chttpbrowsersync.h"
#include "commonddefs.h"

class CProjectManager;

class CRemoteDataStorage : public QObject
{
    Q_OBJECT
public:
    CRemoteDataStorage(QObject * a_pParent = 0);
    ~CRemoteDataStorage();

    void testMethod();
    void connectSignalsAndSlots(CProjectManager & a_rProjectMngr);

public slots:
    void storeProject(KotkaSource::SProjectData const & a_crProjectData);

private:
    void sendNewDataToServer(QJsonObject const & a_crJsonObject);

    CHttpBrowserSync m_oHttpBrowser;
};

#endif // CREMOTEDATASTORAGE_H
