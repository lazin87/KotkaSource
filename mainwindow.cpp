#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QDate>

#include "ccreateprojectdialog.h"
#include "ccreatetaskdialog.h"
#include "cprojectmanager.h"
#include "CContactsDbModel.h"
#include "cremotedatastorage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_oModelIndex(),
    m_pAddProjectAction(0),
    m_pAddSubprojectAction(0),
    m_pAddTaskAction(0),
    m_pEditPrjAction(0)
{
    ui->setupUi(this);
    connect( ui->copyDeadlineDateTimeEdit, SIGNAL(dateTimeChanged(QDateTime const &) )
           , this, SLOT(changeCopyDeadlineSlot(QDateTime const &) )
           );
    connect( ui->deliveryDateTimeEdit, SIGNAL(dateTimeChanged(QDateTime const &) )
           , this, SLOT(changeDeliveryDateSlot(QDateTime const &) )
           );
    connect( ui->nameLineEdit, SIGNAL(returnPressed() )
           , this, SLOT(changeNameSlot() )
           );

    createProjectTreeContextMenu();
    initCalenderWidget();

    m_pServerConnectionStatus = new QLabel("Not Connected");
    ui->statusBar->addWidget(m_pServerConnectionStatus);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
    delete ui;
}

void MainWindow::setModel(QAbstractItemModel *a_pModel)
{
    ui->treeView->setModel(a_pModel);

    QItemSelectionModel * pSelectionModel;
    pSelectionModel = ui->treeView->selectionModel();

    if(0 != pSelectionModel)
    {
        connect( pSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection) )
                 , this, SLOT(selectionChangedSlot(QItemSelection,QItemSelection) )
                 );
    }
}

void MainWindow::setModelForAddressBook(QAbstractTableModel *a_pModel)
{
    ui->addressBookTableView->setModel(a_pModel);
}

void MainWindow::connectSignalsAndSlots(CProjectManager &a_rProjectMngr)
{
    connect( this, SIGNAL(createProject(KotkaSource::SProjectData&,QModelIndex&, QList<KotkaSource::SSourceData> &) )
           , &a_rProjectMngr, SLOT(createProjectSlot(KotkaSource::SProjectData&, QModelIndex&, QList<KotkaSource::SSourceData> &) )
           );

    connect( this, SIGNAL(editProjectSignal(KotkaSource::SProjectData&,QModelIndex&, QList<KotkaSource::SSourceData> &) )
           , &a_rProjectMngr, SLOT(editProjectSlot(KotkaSource::SProjectData&, QModelIndex&, QList<KotkaSource::SSourceData> &) )
           );

    connect( this, SIGNAL(createTask(KotkaSource::STaskData&,QModelIndex&) )
           , &a_rProjectMngr, SLOT(createTaskSlot(KotkaSource::STaskData&,QModelIndex&) )
           );

    connect( this, SIGNAL(editTaskSignal(KotkaSource::STaskData&,QModelIndex&) )
           , &a_rProjectMngr, SLOT(editTaskSlot(KotkaSource::STaskData&,QModelIndex&) )
           );
}

void MainWindow::connectSignalsAndSlots(CContactsDbModel &a_rAddressBook)
{
    connect( this, SIGNAL(addNewContact(KotkaSource::SContactData const &) )
           , &a_rAddressBook, SLOT(addNewContactSlot(KotkaSource::SContactData const &) )
           );
}

void MainWindow::connectSignalsAndSlots(CRemoteDataStorage &a_rRemoteDataStorage)
{
    connect( this, SIGNAL(downloadAllDataSignal() )
           , &a_rRemoteDataStorage, SLOT(downloadAllDataFromServer() )
           );
    connect( this, SIGNAL(checkForUpdatesSignal() )
           , &a_rRemoteDataStorage, SLOT(checkForUpdates() )
           );
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    qDebug() << "MainWindow::selectionChangedSlot()";
    const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
    QString selectedText = ui->treeView->model()->data(oModelIndex, KotkaSource::ProjectDescDispRole).toString();
    ui->textBrowser->setPlainText(selectedText);

    ui->deliveryDateTimeEdit->setDateTime(
                ui->treeView->model()->data(oModelIndex, KotkaSource::DeliveryDateRole).toDateTime()
                );
    ui->copyDeadlineDateTimeEdit->setDateTime(
                ui->treeView->model()->data(oModelIndex, KotkaSource::WritersDeadlineDateRole).toDateTime()
                );
    ui->nameLineEdit->setText(
                ui->treeView->model()->data(oModelIndex, KotkaSource::ObjectNameRole).toString()
                );
    ui->typeDescLabel->setText(
                ui->treeView->model()->data(oModelIndex, KotkaSource::ObjectTypeRole).toString()
                );
}

void MainWindow::changeDeliveryDateSlot(QDateTime const & a_oNewDateTime)
{
    const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
    ui->treeView->model()->setData(oModelIndex, a_oNewDateTime, KotkaSource::DeliveryDateRole);
}

void MainWindow::changeCopyDeadlineSlot(QDateTime const & a_oNewDateTime)
{
    const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
    ui->treeView->model()->setData(oModelIndex, a_oNewDateTime, KotkaSource::WritersDeadlineDateRole);
}

void MainWindow::changeNameSlot()
{
    QString strNewName = ui->nameLineEdit->text();
    const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
    ui->treeView->model()->setData(oModelIndex, strNewName, KotkaSource::ObjectNameRole);
}

void MainWindow::addProjectSlot()
{
    qDebug() << "MainWindow::addProjectSlot()";

    KotkaSource::SProjectData * pProjectData = 0; // usunac wskaznik
    KotkaSource::SProjectData sParentProjectData;
    if(m_oModelIndex.isValid() )
    {
        QVariant rawProjectData = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ReadProjectDataRole);
        sParentProjectData = rawProjectData.value<KotkaSource::SProjectData>();
        pProjectData = &sParentProjectData;
    }
    CCreateProjectDialog newProjectDialog( this
                                         , ui->addressBookTableView->model()
                                         , pProjectData);
    //newProjectDialog.setAddressDbModel(ui->addressBookTableView->model() );

    connect( &newProjectDialog, SIGNAL(addNewContact(KotkaSource::SContactData) )
           , this, SIGNAL(addNewContact(KotkaSource::SContactData) )
           );

    if(QDialog::Accepted == newProjectDialog.exec() )
    {
        KotkaSource::SProjectData sProjectData;
        newProjectDialog.getProjectData(sProjectData);
        // dodac pobieranie wskaznika z modelu ksiazki adresowej

        QList<KotkaSource::SSourceData> sourcesList;
        newProjectDialog.getSourceList(sourcesList);


        emit createProject(sProjectData, m_oModelIndex, sourcesList);
    }
    else
    {

    }
}

void MainWindow::editProjectSlot()
{
    qDebug() << "MainWindow::editProjectSlot()";

    KotkaSource::SProjectData sRootProjectData;
    if(m_oModelIndex.isValid() )
    {
        QVariant rawProjectData = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ReadProjectDataRole);
        sRootProjectData = rawProjectData.value<KotkaSource::SProjectData>();
    }

    CCreateProjectDialog editProjectDialog( this
                                          , ui->addressBookTableView->model()
                                          , &sRootProjectData
                                          , true);

    //editProjectDialog.setAddressDbModel(ui->addressBookTableView->model() );

    connect( &editProjectDialog, SIGNAL(addNewContact(KotkaSource::SContactData) )
           , this, SIGNAL(addNewContact(KotkaSource::SContactData) )
           );

    if(QDialog::Accepted == editProjectDialog.exec() )
    {
        KotkaSource::SProjectData sProjectData;
        editProjectDialog.getProjectData(sProjectData);

        QList<KotkaSource::SSourceData> sourcesList;
        editProjectDialog.getSourceList(sourcesList);

        emit editProjectSignal(sProjectData, m_oModelIndex, sourcesList);
    }
}

void MainWindow::addTaskSlot()
{
    qDebug() << "MainWindow::addTaskSlot()";

    QVariant rawProjectData = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ReadProjectDataRole);
    KotkaSource::SProjectData sParentProjectData = rawProjectData.value<KotkaSource::SProjectData>();
    CCreateTaskDialog newTaskDialog( &sParentProjectData, this);

    if(QDialog::Accepted == newTaskDialog.exec() )
    {
        KotkaSource::STaskData sTaskData;
        newTaskDialog.getData(sTaskData);

        emit createTask(sTaskData, m_oModelIndex);
    }
    else
    {

    }
}

void MainWindow::editTaskSlot()
{
    KotkaSource::STaskData sTaskData;
    qDebug() << "MainWindow::editTaskSlot(): " << m_oModelIndex;
    if(m_oModelIndex.isValid() )
    {
        QVariant rawProjectData = ui->treeView->model()->data(m_oModelIndex.parent(), KotkaSource::ReadProjectDataRole);
        QVariant rawTaskData = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ReadTaskDataRole);
        QVariant rawTaskName = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ObjectNameRole);
        KotkaSource::SProjectData sParentProjectData = rawProjectData.value<KotkaSource::SProjectData>();
        sTaskData = rawTaskData.value<KotkaSource::STaskData>();
        qDebug() << "MainWindow::editTaskSlot() task name1: " << sTaskData.m_strName;
        qDebug() << "MainWindow::editTaskSlot() task name2: " << rawTaskName.toString();
        CCreateTaskDialog editTaskDialog(&sParentProjectData, &sTaskData, this);


        if(QDialog::Accepted == editTaskDialog.exec() )
        {
            KotkaSource::STaskData sTaskData;
            editTaskDialog.getData(sTaskData);

          //  emit editTaskSignal(sTaskData, m_oModelIndex);
        }
    }
    else
    {
        qWarning() << "MainWindow::editTaskSlot(): invalid model index";
    }
    //oRootTaskIndex.parent()
}

void MainWindow::onProjTreeContextMenu(const QPoint &a_rcPoint)
{
    qDebug() << "MainWindow::onProjTreeContextMenu()";

    m_oModelIndex = ui->treeView->indexAt(a_rcPoint);
    QMenu oContextMenu;

    if( m_oModelIndex.isValid() )
    {
        bool isProject = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ObjectTypeRole) != "Task";

        if(isProject)
        {
            oContextMenu.addAction(m_pAddSubprojectAction);
            oContextMenu.addAction(m_pAddTaskAction);
            oContextMenu.addAction(m_pEditPrjAction);
        }
        else
        {
            oContextMenu.addAction(m_pEditTaskAction);
        }
    }
    else
    {
        oContextMenu.addAction(m_pAddProjectAction);
    }

    oContextMenu.exec(ui->treeView->mapToGlobal(a_rcPoint) );
}

void MainWindow::downloadAllDataSlot()
{
    emit downloadAllDataSignal();
}

void MainWindow::checkForUpdatesSlot()
{
    emit checkForUpdatesSignal();
}

void MainWindow::createProjectTreeContextMenu()
{
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect( ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &) )
           , this, SLOT(onProjTreeContextMenu(const QPoint &) )
           );

    m_pAddProjectAction = new QAction("Add new project", ui->treeView);
    connect( m_pAddProjectAction, SIGNAL(triggered() )
           , this, SLOT(addProjectSlot() )
           );

    m_pAddSubprojectAction = new QAction("Add subproject", ui->treeView);
    connect( m_pAddSubprojectAction, SIGNAL(triggered() )
           , this, SLOT(addProjectSlot() )
           );

    m_pAddTaskAction = new QAction("Add task", ui->treeView);
    connect( m_pAddTaskAction, SIGNAL(triggered() )
           , this, SLOT(addTaskSlot() )
           );

    m_pEditPrjAction = new QAction("Edit project", ui->treeView);
    connect( m_pEditPrjAction, SIGNAL(triggered() )
           , this, SLOT(editProjectSlot() )
           );

    m_pEditTaskAction = new QAction("Edit task", ui->treeView);
    connect( m_pEditTaskAction, SIGNAL(triggered() )
           , this, SLOT(editTaskSlot() )
           );



}

void MainWindow::initCalenderWidget()
{
    QDate oToday = QDate::currentDate();
    QTextCharFormat oTodayFormat;
    QFont oTodayFont;
    oTodayFont.setBold(true);
    oTodayFormat.setFont(oTodayFont);
    oTodayFormat.setBackground(QBrush(QColor::fromRgb(240,240,240) ) );

    ui->calendarWidget->setSelectedDate(oToday);
    ui->calendarWidget->setDateTextFormat(oToday, oTodayFormat);
}
