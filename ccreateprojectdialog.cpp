#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

CCreateProjectDialog::CCreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCreateProjectDialog)
{
    ui->setupUi(this);
}

CCreateProjectDialog::~CCreateProjectDialog()
{
    delete ui;
}
