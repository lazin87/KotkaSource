#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QItemSelection>
#include <QItemSelectionModel>

#include "ccreateprojectdialog.h"
#include "ccreatetaskdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_oModelIndex(),
    m_pAddProjectAction(0),
    m_pAddSubprojectAction(0),
    m_pAddTaskAction(0)
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
    CCreateProjectDialog newProjectDialog(this);
    newProjectDialog.setAddressDbToCompleter(ui->addressBookTableView->model() );

    connect( &newProjectDialog, SIGNAL(addNewContact(KotkaSource::SContactData) )
           , this, SIGNAL(addNewContact(KotkaSource::SContactData) )
           );

    if(QDialog::Accepted == newProjectDialog.exec() )
    {
        KotkaSource::SProjectData sProjectData;
        newProjectDialog.getData(sProjectData);
        // dodac pobieranie wskaznika z modelu ksiazki adresowej


        emit createProject(sProjectData, m_oModelIndex);
    }
    else
    {

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
        qDebug() << "MainWindow::addTaskSlot() emit";

        emit createTask(sTaskData, m_oModelIndex);
    }
    else
    {

    }
}

void MainWindow::onProjTreeContextMenu(const QPoint &a_rcPoint)
{
    qDebug() << "MainWindow::onProjTreeContextMenu()";

    m_oModelIndex = ui->treeView->indexAt(a_rcPoint);
    if( m_oModelIndex.isValid() )
    {
        bool isProject = ui->treeView->model()->data(m_oModelIndex, KotkaSource::ObjectTypeRole) != "Task";

        if(isProject)
        {
            QMenu oContextMenu;
            oContextMenu.addAction(m_pAddSubprojectAction);
            oContextMenu.addAction(m_pAddTaskAction);
            oContextMenu.exec(ui->treeView->mapToGlobal(a_rcPoint) );
        }
    }
    else
    {
        QMenu oContextMenu;
        oContextMenu.addAction(m_pAddProjectAction);
        oContextMenu.exec(ui->treeView->mapToGlobal(a_rcPoint) );
    }
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



}
