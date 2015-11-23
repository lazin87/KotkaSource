#include "ccreatecontactdialog.h"
#include "ui_ccreatecontactdialog.h"

CCreateContactDialog::CCreateContactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCreateContactDialog)
{
    ui->setupUi(this);
}

CCreateContactDialog::~CCreateContactDialog()
{
    delete ui;
}
