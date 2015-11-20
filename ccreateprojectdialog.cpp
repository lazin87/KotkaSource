#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

#include <QCompleter>
#include <QDebug>

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

void CCreateProjectDialog::getData(KotkaSource::SProjectData &a_rProjectData) const
{
    a_rProjectData.m_strName = ui->projectNamelineEdit->text();
    a_rProjectData.m_oDateTimeDelivery = ui->deliveryDateTimeEdit->dateTime();
    a_rProjectData.m_oDateTimeWriterDeadline = ui->writersDeadlineDateTimeEdit->dateTime();
}

void CCreateProjectDialog::setAddressDbToCompleter(QAbstractItemModel *a_pModel)
{
    if(0 != a_pModel )
    {
        /*QCompleter **/completer = new QCompleter(this);
        completer->setModel(a_pModel);
        ui->clientComboBox->setCompleter(completer);

        connect( completer, SIGNAL(activated(const QModelIndex &) )
               , this, SLOT(selectedClientChangedSlot(const QModelIndex &) )
               );
    }
    else
    {
        qWarning() << "CCreateProjectDialog::setAddressDbToCompleter"
                   << " Model: " << a_pModel
                   << " Completer: " << ui->clientComboBox->completer();
    }
}

void CCreateProjectDialog::accept()
{
    if(validateInputData() )
    {
        QDialog::accept();
    }
}

void CCreateProjectDialog::selectedClientChangedSlot(const QModelIndex &a_rModelIndex)
{
    qDebug() << "CCreateProjectDialog::selectedClientChangedSlot:"
             << " row: " << a_rModelIndex.row()
             << " column: " << a_rModelIndex.column();

    setEmail(a_rModelIndex);
    setPhone(a_rModelIndex);
    setAddress(a_rModelIndex);
}

void CCreateProjectDialog::setEmail(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->model()->data( a_rModelIndex
                                                                        , KotkaSource::ObjectEmailRole
                                                                        );
        strTemp = rawVal.isValid() ? rawVal.toString() : strTemp;
    }
    ui->emailDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setPhone(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->model()->data( a_rModelIndex
                                                                        , KotkaSource::ObjectPhoneRole
                                                                        );
        strTemp = rawVal.isValid() ? rawVal.toString() : strTemp;
    }

    qDebug() << "CCreateProjectDialog::setPhone: phone: |" << strTemp << "|";
    ui->phoneDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setAddress(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->model()->data( a_rModelIndex
                                                                        , KotkaSource::ObjectAddressRole
                                                                        );
        strTemp = rawVal.isValid() ? rawVal.toString() : strTemp;
    }
    ui->addressDispLabel->setText(strTemp);
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
