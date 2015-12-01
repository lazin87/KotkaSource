#ifndef CLOCALDATASTORAGE_H
#define CLOCALDATASTORAGE_H

#include <QObject>

class CLocalDataStorage : public QObject
{
    Q_OBJECT
public:
    CLocalDataStorage(QObject * a_pParent = 0);
    ~CLocalDataStorage();

    void readProjectData();
    void readContactData();

public slots:
//    void saveNewProject();
//    void saveNewTask();
//    void saveNewSource();
//    void saveNewContact();

//    void updateNewProject();
//    void updateNewTask();
//    void updateNewSource();
//    void updateNewContact();

//    void removeNewProject();
//    void removeNewTask();
//    void removeNewSource();
//    void removeNewContact();

private:
    bool init();

    bool createProjectTab();
    bool createTaskTab();
    bool createAdressTab();
    bool createSourceTab();
};

#endif // CLOCALDATASTORAGE_H
