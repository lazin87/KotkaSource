#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

CCreateProjectDialog::CCreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCreateProjectDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
}

CCreateProjectDialog::~CCreateProjectDialog()
{
    delete ui;
}

QString CCreateProjectDialog::getName() const
{
    return ui->projectNamelineEdit->text();
}

QDateTime CCreateProjectDialog::getDeliveryDate() const
{
    return ui->deliveryDateTimeEdit->dateTime();
}

QDateTime CCreateProjectDialog::getWritersDeadline() const
{
    return ui->writersDeadlineDateTimeEdit->dateTime();
}

void CCreateProjectDialog::accept()
{
    if(validateInputData() )
    {
        QDialog::accept();
    }
}

bool CCreateProjectDialog::validateInputData() const
{
    bool fResult = true;

    fResult &= validateProjectName();
    fResult &= validateDeadlinesDates();
    fResult &= validateClient();

    ui->errorLabel->setText( fResult ? "" : "Invalid input data! Please correct the form." );

    return fResult;
}

bool CCreateProjectDialog::validateProjectName() const
{
    bool fResult = true;
    QString strTemp = ui->projectNamelineEdit->text();
    strTemp = strTemp.simplified();
    strTemp.replace(" ", "" );

    fResult &= !strTemp.isEmpty();

    ui->projectNamelineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    return fResult;
}

bool CCreateProjectDialog::validateDeadlinesDates() const
{
    bool fResult = true;
    QDateTime currentDate = QDateTime::currentDateTime();


    fResult &= currentDate <= ui->writersDeadlineDateTimeEdit->dateTime();
    ui->writersDeadlineDateTimeEdit->setStyleSheet(
                fResult ? "" : "QDateTimeEdit { background-color : red; }"
                );

    fResult &= ui->deliveryDateTimeEdit->dateTime() >= ui->writersDeadlineDateTimeEdit->dateTime();
    ui->deliveryDateTimeEdit->setStyleSheet(
                fResult ? "" : "QDateTimeEdit { background-color : red; }"
                );


    return fResult;
}

bool CCreateProjectDialog::validateClient() const
{
    bool fResult = true;

    return fResult;
}
