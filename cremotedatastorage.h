#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>
#include "chttpbrowsersync.h"

class CRemoteDataStorage : public QObject
{
    Q_OBJECT
public:
    CRemoteDataStorage(QObject * a_pParent = 0);
    ~CRemoteDataStorage();

    void testMethod();
private:

    CHttpBrowserSync m_oHttpBrowser;
};

#endif // CREMOTEDATASTORAGE_H
