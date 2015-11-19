#include "ccreatetaskdialog.h"
#include "ui_ccreatetaskdialog.h"


CCreateTaskDialog::CCreateTaskDialog(const KotkaSource::SProjectData *a_pParentProjectData
                                    , QWidget *parent):
    QDialog(parent),
    ui(new Ui::CCreateTaskDialog)
{
    ui->setupUi(this);
}

CCreateTaskDialog::~CCreateTaskDialog()
{
    delete ui;
}
