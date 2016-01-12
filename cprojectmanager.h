#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H

#include <QObject>
#include <QStandardItemModel>
#include<QMap>

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

signals:
    void projectModelWasChanged(QAbstractItemModel *);
    void projectWasCreated(KotkaSource::SProjectData const &);
    void taskWasCreated(KotkaSource::STaskData const &);
    void dataUpdateSignal(KotkaSource::SProjectData const & a_crProjectData, QString const & a_crOldName);
    void dataUpdateSignal(KotkaSource::STaskData const & a_crTaskData, QString const & a_crOldName);

public slots:
    void createProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex, QList<KotkaSource::SSourceData> &a_rSourcesDataList);
    void editProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex, QList<KotkaSource::SSourceData> &a_rSourcesDataList);
    void createTaskSlot(KotkaSource::STaskData &a_rTaskData, QModelIndex &a_rModelIndex);
    void editTaskSlot(KotkaSource::STaskData &a_rTaskData, QModelIndex &a_rModelIndex);
    void loadProjectsModel( const QList<KotkaSource::SProjectData> & a_crProjectDataList
                          , const QList<KotkaSource::STaskData> & a_crTasksDataList
                          , const QList<KotkaSource::SSourceData> & a_crSourcesData );

private slots:
    void updateModelSlot();

private:
    void prepareDirs();

    void buildProjectsHierarchy( const QList<KotkaSource::SProjectData> &a_crProjectDataList
                               , QMap<QString, QStandardItem *> & mapOfProjectbyName );

    void addTasksToProjectHierarchy(const QList<KotkaSource::STaskData> & a_crTasksDataList
                                   /*, const QList<KotkaSource::STaskObjectData> & a_crTaskObjectsData */ // should be added eariler to STaskData
                                   , QMap<QString, QStandardItem *> & a_rMapOfProjectbyName );

    void addSourcesToProjectHierarchy( const QList<KotkaSource::SSourceData> & a_crSourcesData
                                     , QMap<QString, QStandardItem *> & a_rMapOfProjectbyName );

    QStandardItemModel m_oModel;
};

#endif // CPROJECTMANAGER_H
