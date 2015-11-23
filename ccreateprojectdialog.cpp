#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

#include <QCompleter>
#include <QDebug>

#include "ccreatecontactdialog.h"

CCreateProjectDialog::CCreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCreateProjectDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
    ui->clientErrorLabel->setStyleSheet("QLabel { color : red; }");
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
    a_rProjectData.m_strClientName = ui->clientComboBox->currentText();
}

void CCreateProjectDialog::setAddressDbToCompleter(QAbstractItemModel *a_pModel)
{
    if(0 != a_pModel )
    {
        QCompleter * completer = new QCompleter(this);
        completer->setModel(a_pModel);
        ui->clientComboBox->setCompleter(completer);

        connect( completer, SIGNAL(highlighted(const QModelIndex &) )
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

QString CCreateProjectDialog::getClientName() const
{
    return ui->clientComboBox->currentText();
}

void CCreateProjectDialog::accept()
{
    if(validateInputData() )
    {
        QDialog::accept();
    }
}

void CCreateProjectDialog::clientAddSlot()
{
    QString strClientName = ( ui->clientComboBox->completer()->currentIndex().isValid() ) ?
                "" :
                ui->clientComboBox->currentText().simplified();

    CCreateContactDialog oCreateContactDialog(this, strClientName);

    if(QDialog::Accepted == oCreateContactDialog.exec() )
    {

    }
}

void CCreateProjectDialog::clientEditSlot()
{
    QModelIndex oClientIndex = ui->clientComboBox->completer()->currentIndex();

    if(  !(ui->clientComboBox->currentText().isEmpty() )
      && oClientIndex.isValid()
      )
    {
        QVariant rawData =
                ui->clientComboBox->completer()->completionModel()->data( oClientIndex,
                                                                          KotkaSource::ReadContactDataRole
                                                                        );
        KotkaSource::SContactData clientContactData = rawData.value<KotkaSource::SContactData>();

        CCreateContactDialog oEditContactDialog(this, clientContactData);

        if(QDialog::Accepted == oEditContactDialog.exec() )
        {

        }
    }
}

void CCreateProjectDialog::selectedClientChangedSlot(const QModelIndex &a_rModelIndex)
{
    setEmail(a_rModelIndex);
    setPhone(a_rModelIndex);
    setAddress(a_rModelIndex);
}

void CCreateProjectDialog::setErrorMsg(const QString &a_strErrorMsg) const
{
     ui->errorLabel->setText(a_strErrorMsg);
}

void CCreateProjectDialog::setEmail(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->completionModel()->data( a_rModelIndex
                                                                                  , KotkaSource::ObjectEmailRole
                                                                                  );
        strTemp = rawVal.toString();
    }
    ui->emailDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setPhone(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->completionModel()->data( a_rModelIndex
                                                                                  , KotkaSource::ObjectPhoneRole
                                                                                  );
        strTemp = rawVal.toString();
    }
    ui->phoneDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setAddress(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() )
    {
        QVariant rawVal = ui->clientComboBox->completer()->completionModel()->data( a_rModelIndex
                                                                                  , KotkaSource::ObjectAddressRole
                                                                                  );
        strTemp = rawVal.toString();
    }
    ui->addressDispLabel->setText(strTemp);
}

bool CCreateProjectDialog::validateInputData() const
{
    bool fResult = true;

    fResult &= validateProjectName();
    fResult &= validateDeadlinesDates();
    fResult &= validateClient();

    setErrorMsg( fResult ? "" : "Invalid input data! Please correct the form." );

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
    QString clientErrMsg = "";

    //sprawdzic czy string ok
    QString strTemp = ui->clientComboBox->currentText();
    strTemp = strTemp.simplified();
    strTemp.replace(" ", "" );

    fResult &= !strTemp.isEmpty();
    ui->clientComboBox->setStyleSheet(
                fResult ? "" : "QComboBox {background-color : red; }"
                          );
    clientErrMsg = fResult ? ""
                           : "Please enter a client name.";

    //sprawdzic czy istnieje
    if(fResult)
    {
        QModelIndex oModeIndex = ui->clientComboBox->completer()->currentIndex();
        fResult &= oModeIndex.isValid();

        if(!fResult)
        {
            qWarning() << "CCreateProjectDialog::validateClient(): WPIS NIE ISTNIEJE";
        }

        ui->clientComboBox->setStyleSheet(
                    fResult ? "" : "QComboBox {background-color : red; }"
                              );
        clientErrMsg = fResult ? ""
                               : "Contact does not exist. Press Add button to create a new contact.";
    }

    //sprawdzic czy ma atrybut klienta
    if(fResult)
    {
        QModelIndex oModeIndex = ui->clientComboBox->completer()->currentIndex();
        QVariant rawVal = ui->clientComboBox->completer()->completionModel()->data( oModeIndex
                                                                                  , KotkaSource::ContactIsClientRole
                                                                                  );
        fResult &= rawVal.toBool();

        ui->clientComboBox->setStyleSheet(
                    fResult ? "" : "QComboBox {background-color : yellow; }"
                              );
        clientErrMsg = fResult ? ""
                               : "Contact is not a client. Press Edit button to add client attribute.";
    }

    ui->clientErrorLabel->setText(clientErrMsg);

    return fResult;
}
