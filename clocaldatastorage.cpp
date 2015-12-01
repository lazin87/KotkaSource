#include "clocaldatastorage.h"

#include <QtSql>
#include <QDebug>

CLocalDataStorage::CLocalDataStorage(QObject *a_pParent)
    : QObject(a_pParent)
{
    QSqlDatabase oDb = QSqlDatabase::addDatabase("QSQLITE");
    oDb.setDatabaseName("first.db");
    oDb.open();

    QSqlQuery oQuery;
    bool result = oQuery.exec("create table person "
                "(id integer primary key, "
                "firstname varchar(20), "
                "lastname varchar(30), "
                "age integer)");

    qDebug() << "CLocalDataStorage::CLocalDataStorage() " << result;

}

CLocalDataStorage::~CLocalDataStorage()
{

}

void CLocalDataStorage::readProjectData()
{

}

bool CLocalDataStorage::init()
{
    bool fResult = true;

    fResult &= createProjectTab();
    fResult &= createAdressTab();
    fResult &= createSourceTab();
    fResult &= createTaskTab();

    return fResult;
}

bool CLocalDataStorage::createProjectTab()
{
    bool fResult = false;
    QSqlQuery oQuery;

    QString strQuery = "create table if not exist project "
                       "(id integer primary key, "
                       "name varchar(20), "
                       "clientName varchar(30), "
                       "age integer)";

    fResult = oQuery.exec(strQuery);

    return fResult;
}

bool CLocalDataStorage::createTaskTab()
{
    return true;
}

bool CLocalDataStorage::createAdressTab()
{
    return true;
}

bool CLocalDataStorage::createSourceTab()
{
    return true;
}

