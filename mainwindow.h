#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "commonddefs.h"
#include <QModelIndex>

class QAbstractItemModel;
class QItemSelectionModel;
class QItemSelection;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setModel(QAbstractItemModel * a_pModel);
    void setModelForAddressBook(QAbstractTableModel * a_pModel);

signals:
    void createProject(KotkaSource::SProjectData &, QModelIndex &, QList<KotkaSource::SSourceData> &);
    void createTask(KotkaSource::STaskData &, QModelIndex &);
    void addNewContact(KotkaSource::SContactData const & a_crContactData);
    void editContact(KotkaSource::SContactData const & a_crContactData);
    void downloadAllDataSignal();

private slots:
    void selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/ );
    void changeDeliveryDateSlot(const QDateTime &a_oNewDateTime);
    void changeCopyDeadlineSlot(QDateTime const & a_oNewDateTime);
    void changeNameSlot();

    void addProjectSlot();
    void addTaskSlot();
    void onProjTreeContextMenu(const QPoint & a_rcPoint);

    void downloadAllDataSlot();

private:
    void createProjectTreeContextMenu();

    Ui::MainWindow *ui;
    QModelIndex m_oModelIndex;

    QAction * m_pAddProjectAction;
    QAction * m_pAddSubprojectAction;
    QAction * m_pAddTaskAction;

    QLabel * m_pServerConnectionStatus;

};

#endif // MAINWINDOW_H
