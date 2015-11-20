#include "ccreatetaskdialog.h"
#include "ui_ccreatetaskdialog.h"

#include <QDebug>

CCreateTaskDialog::CCreateTaskDialog(const KotkaSource::SProjectData *a_pParentProjectData
                                    , QWidget *parent):
    QDialog(parent),
    ui(new Ui::CCreateTaskDialog),
    m_pParentProjectData(a_pParentProjectData)
{
    ui->setupUi(this);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");

    if(0 != a_pParentProjectData)
    {
        ui->deliveryDateTimeEdit->setDateTime(a_pParentProjectData->m_oDateTimeDelivery);
        ui->writerDeadlineDateTimeEdit->setDateTime(a_pParentProjectData->m_oDateTimeWriterDeadline);
    }
    else
    {
        qDebug() << "CCreateTaskDialog::CCreateTaskDialog NULL PTR";
    }
}

CCreateTaskDialog::~CCreateTaskDialog()
{
    delete ui;
}

void CCreateTaskDialog::getData(KotkaSource::STaskData &a_rTaskData) const
{
    a_rTaskData.m_strName = ui->nameLineEdit->text();
    a_rTaskData.m_oDateTimeDelivery = ui->deliveryDateTimeEdit->dateTime();
    a_rTaskData.m_oDateTimeWriterDeadline = ui->writerDeadlineDateTimeEdit->dateTime();
}

void CCreateTaskDialog::setAddressDbToCompleter(QAbstractItemModel *a_pModel)
{

}

void CCreateTaskDialog::accept()
{
    if(validateInputData() )
    {
        QDialog::accept();
    }
}

bool CCreateTaskDialog::validateInputData() const
{
    bool fResult = true;

    fResult &= validateProjectName();
    fResult &= validateDeadlinesDates();

    ui->errorLabel->setText( fResult ? "" : "Invalid input data! Please correct the form." );

    return fResult;
}

bool CCreateTaskDialog::validateProjectName() const
{
    bool fResult = true;
    QString strTemp = ui->nameLineEdit->text();
    strTemp = strTemp.simplified();
    strTemp.replace(" ", "" );

    fResult &= !strTemp.isEmpty();

    ui->nameLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    return fResult;
}

bool CCreateTaskDialog::validateDeadlinesDates() const
{
    bool fResult = true;

    if(0 != m_pParentProjectData)
    {
        fResult &= m_pParentProjectData->m_oDateTimeWriterDeadline >= ui->writerDeadlineDateTimeEdit->dateTime();
        ui->writerDeadlineDateTimeEdit->setStyleSheet(
                    fResult ? "" : "QDateTimeEdit { background-color : red; }"
                              );

        fResult &= m_pParentProjectData->m_oDateTimeDelivery >= ui->deliveryDateTimeEdit->dateTime();
        ui->deliveryDateTimeEdit->setStyleSheet(
                    fResult ? "" : "QDateTimeEdit { background-color : red; }"
                              );
    }
    else
    {
        fResult = false;
        ui->writerDeadlineDateTimeEdit->setStyleSheet("QDateTimeEdit { background-color : red; }");
        ui->deliveryDateTimeEdit->setStyleSheet("QDateTimeEdit { background-color : red; }");
    }


    return fResult;
}
