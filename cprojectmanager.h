#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H

#include <QObject>
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

signals:
    void projectModelWasChanged(QAbstractItemModel *);

public slots:
    void createProjectSlot(KotkaSource::SProjectData &a_rProjectData, QModelIndex &a_rModelIndex, QList<KotkaSource::SSourceData> &a_rSourcesDataList);
    void createTaskSlot(KotkaSource::STaskData &a_rTaskData, QModelIndex &a_rModelIndex);

private slots:
    void updateModelSlot();

private:
    void prepareDirs();
    QStandardItemModel m_oModel;
};

#endif // CPROJECTMANAGER_H
