#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
   // ui->treeView->de
    delete ui;
}

void MainWindow::setModel(QAbstractItemModel *a_pModel)
{
    ui->treeView->setModel(a_pModel);
}
