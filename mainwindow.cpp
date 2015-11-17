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
            //oModelIndex.data(Qt::DisplayRole).toString();
    ui->textBrowser->setPlainText(selectedText);
}
