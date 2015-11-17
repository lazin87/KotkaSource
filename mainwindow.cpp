#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QItemSelection>
#include <QItemSelectionModel>

#include "commonddefs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
