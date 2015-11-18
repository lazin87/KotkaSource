#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>

#include "commonddefs.h"

class IProject;

class CProjectManager : public QObject
{
    Q_OBJECT
public:
    CProjectManager(QObject * a_pParent = 0);
    ~CProjectManager();

    QStandardItemModel * getModel();

    bool createProject(QString a_strName);
    bool createSubproject(IProject & a_rProject, QString a_strName);
    bool createTask(IProject & a_rProject, QString a_strName);
    IProject * getProject(int a_iIndex);

signals:
    void projectModelWasChanged(QAbstractItemModel *);

public slots:
    void createProjectSlot(KotkaSource::SProjectData &a_rProjectData);

private slots:
    void updateModelSlot();

private:
    void prepareModel();
    void removeProjects();

    QStandardItemModel m_oModel;
    QList<IProject *> m_pProjetsList;
};

#endif // CPROJECTMANAGER_H
