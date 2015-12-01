#ifndef CREMOTEDATASTORAGE_H
#define CREMOTEDATASTORAGE_H

#include <QObject>

class CRemoteDataStorage : public QObject
{
    Q_OBJECT
public:
    CRemoteDataStorage(QObject * a_pParent = 0);
    ~CRemoteDataStorage();
};

#endif // CREMOTEDATASTORAGE_H
