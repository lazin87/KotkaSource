#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QItemSelection>
#include <QItemSelectionModel>

#include "commonddefs.h"
#include "ccreateprojectdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pAddProjectAction(0),
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
    QItemSelectionModel * pSelectionModel;
    ui->treeView->setModel(a_pModel);
    pSelectionModel = ui->treeView->selectionModel();

    if(0 != pSelectionModel)
    {
        connect( pSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection) )
                 , this, SLOT(selectionChangedSlot(QItemSelection,QItemSelection) )
                 );
    }
    else
    {
        qWarning() << "MainWindow::setModel() : NULL PTR";
    }
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
                ui->treeView->model()->data(oModelIndex, KotkaSource::DeadlineDateRole).toDateTime()
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
    ui->treeView->model()->setData(oModelIndex, a_oNewDateTime, KotkaSource::DeadlineDateRole);
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

    if(QDialog::Accepted == newProjectDialog.exec() )
    {
        const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
        ui->treeView->model()->setData(oModelIndex, newProjectDialog.getName(), KotkaSource::CreateNewProjectRole);
    }
    else
    {

    }
}

void MainWindow::addTaskSlot()
{
    qDebug() << "MainWindow::addTaskSlot()";
}

void MainWindow::onProjTreeContextMenu(const QPoint &a_rcPoint)
{
    qDebug() << "MainWindow::onProjTreeContextMenu()";

    QModelIndex oIndex = ui->treeView->indexAt(a_rcPoint);
    if( oIndex.isValid() )
    {
        const QModelIndex oModelIndex = ui->treeView->selectionModel()->currentIndex();
        bool isProject = ui->treeView->model()->data(oModelIndex, KotkaSource::ObjectTypeRole) != "Task";

        if(isProject)
        {
            QMenu oContextMenu;
            oContextMenu.addAction(m_pAddProjectAction);
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

    m_pAddProjectAction = new QAction("Add project", ui->treeView);
    connect( m_pAddProjectAction, SIGNAL(triggered() )
           , this, SLOT(addProjectSlot() )
           );

    m_pAddTaskAction = new QAction("Add task", ui->treeView);
    connect( m_pAddTaskAction, SIGNAL(triggered() )
           , this, SLOT(addTaskSlot() )
           );



}
