#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

#include <QCompleter>
#include <QDebug>
#include <QFileDialog>
#include <QDir>

#include "ccreatecontactdialog.h"

CCreateProjectDialog::CCreateProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCreateProjectDialog)
{
    ui->setupUi(this);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
    ui->clientErrorLabel->setStyleSheet("QLabel { color : red; }");

    setupSourcesTable();
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

void CCreateProjectDialog::getProjectData(KotkaSource::SProjectData &a_rProjectData) const
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

//        connect( completer, SIGNAL(highlighted(const QModelIndex &) )
//               , this, SLOT(selectedClientChangedSlot(const QModelIndex &) )
//               );
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
    QString strClientName = findClientIndex(ui->clientComboBox->currentText() ).isValid() ?
                "" :
                ui->clientComboBox->currentText().simplified();

    CCreateContactDialog oCreateContactDialog(this, strClientName);
    oCreateContactDialog.setAddressBookModel(ui->clientComboBox->completer()->model() );

    if(QDialog::Accepted == oCreateContactDialog.exec() )
    {
        qDebug() << "CCreateProjectDialog::clientAddSlot()";
        KotkaSource::SContactData sContactData;
        oCreateContactDialog.getContactData(sContactData);
        fillInClientInformation(sContactData);

        emit addNewContact(sContactData);
    }
}

void CCreateProjectDialog::clientEditSlot()
{
    if(false == ui->clientComboBox->currentText().isEmpty() )
    {
        QModelIndex oClientIndex = findClientIndex(ui->clientComboBox->currentText() );

        if(oClientIndex.isValid() )
        {
            QVariant rawData =
                    ui->clientComboBox->completer()->model()->data( oClientIndex,
                                                                    KotkaSource::ReadContactDataRole
                                                                    );
            KotkaSource::SContactData clientContactData = rawData.value<KotkaSource::SContactData>();
            CCreateContactDialog oEditContactDialog(this, clientContactData);

            if(QDialog::Accepted == oEditContactDialog.exec() )
            {
                KotkaSource::SContactData sContactData;
                oEditContactDialog.getContactData(sContactData);

                fillInClientInformation(sContactData);
                ui->clientComboBox->completer()->model()->setData(
                            oClientIndex
                            , QVariant::fromValue(sContactData)
                            , KotkaSource::SetContactDataRole );
            }
        }
    }
}

void CCreateProjectDialog::setErrorMsg(const QString &a_strErrorMsg) const
{
    ui->errorLabel->setText(a_strErrorMsg);
}

void CCreateProjectDialog::clientNameWasChangedSlot(const QString &a_rNewName)
{
    QModelIndex oClientIndex = findClientIndex(a_rNewName);
    fillInClientInformation(oClientIndex);
}

void CCreateProjectDialog::sourceAddSlot()
{
    qDebug() << "CCreateProjectDialog::sourceAddSlot()";
    QStringList fileNames = QFileDialog::getOpenFileNames( this
                                                   , "Open File"
                                                   , QDir::homePath()
                                                   , "All files (*.*)"
                                                   );

    if(0 < fileNames.count() )
    {
        addNewEntriesToSourcesTable(fileNames);
    }
    else
    {
        qDebug() << "CCreateProjectDialog::sourceAddSlot(): no files were selected";
    }
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

void CCreateProjectDialog::fillInClientInformation(const KotkaSource::SContactData &a_rContactData)
{
    ui->clientComboBox->setCurrentText(a_rContactData.m_strName);
    ui->emailDispLabel->setText(a_rContactData.m_strEmail);
    ui->phoneDispLabel->setText(a_rContactData.m_strPhone);
    ui->addressDispLabel->setText(a_rContactData.m_strAddress);
}

void CCreateProjectDialog::fillInClientInformation(const QModelIndex &a_rModelIndex)
{
    setEmail(a_rModelIndex);
    setPhone(a_rModelIndex);
    setAddress(a_rModelIndex);
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
        QModelIndex oClientIndex = findClientIndex(ui->clientComboBox->currentText() );
        fResult = oClientIndex.isValid();

        qDebug() << "CCreateProjectDialog::validateClient(): str to match: " << ui->clientComboBox->currentText();
        if(!fResult)
        {
            qWarning() << "CCreateProjectDialog::validateClient(): WPIS NIE ISTNIEJE";
        }

        ui->clientComboBox->setStyleSheet(
                    fResult ? "" : "QComboBox {background-color : red; }"
                              );
        clientErrMsg = fResult ? ""
                               : "Contact does not exist. Press Add button to create a new contact.";

        //sprawdzic czy ma atrybut klienta
        if(fResult)
        {
            fResult = checkIfClient(oClientIndex);

            ui->clientComboBox->setStyleSheet(
                        fResult ? "" : "QComboBox {background-color : yellow; }"
                                  );
            clientErrMsg = fResult ? ""
                                   : "Contact is not a client. Press Edit button to add client attribute.";
        }
    }

    ui->clientErrorLabel->setText(clientErrMsg);

    return fResult;
}

QModelIndex CCreateProjectDialog::findClientIndex(const QString &a_rStrName) const
{
    QModelIndex oStartIndex = ui->clientComboBox->completer()->model()->index(0, CPersonPropertis::toInt(CPersonPropertis::eName) );
    QModelIndexList oModelIndexList = ui->clientComboBox->completer()->model()->match( oStartIndex
                                                                  , Qt::DisplayRole
                                                                  , ui->clientComboBox->currentText()
                                                                  , 1
                                                                  , Qt::MatchFixedString
                                                                  );
    return  (oModelIndexList.isEmpty() ) ? QModelIndex() : oModelIndexList[0];
}

bool CCreateProjectDialog::checkIfClient(const QModelIndex &a_rIndex) const
{
    QVariant rawVal = ui->clientComboBox->completer()->model()->data( a_rIndex
                                                                    , KotkaSource::ContactIsClientRole
                                                                    );
    return rawVal.toBool();
}

void CCreateProjectDialog::setupSourcesTable()
{
    QStringList headerSorucesTable;
    headerSorucesTable << CSourcePropertis::s_aPropertisLabels[CSourcePropertis::eName]
                       << CSourcePropertis::s_aPropertisLabels[CSourcePropertis::eIsReadOnly]
                       << CSourcePropertis::s_aPropertisLabels[CSourcePropertis::eParser];
    ui->sourcesTableWidget->setColumnWidth(0, 300);
    ui->sourcesTableWidget->setColumnWidth(1, 80);
    ui->sourcesTableWidget->setColumnWidth(2, 100);
    ui->sourcesTableWidget->setHorizontalHeaderLabels(headerSorucesTable);
}

void CCreateProjectDialog::addNewEntriesToSourcesTable(const QStringList &a_strPathList)
{
    foreach(const QString str, a_strPathList)
    {
        if(false == str.isEmpty() )
        {
            int iNewRowIndex = ui->sourcesTableWidget->rowCount();
            ui->sourcesTableWidget->insertRow(iNewRowIndex);

            ui->sourcesTableWidget->setItem(iNewRowIndex, 0, new QTableWidgetItem(str) );
            QTableWidgetItem * pWidgetItem = new QTableWidgetItem("");
            pWidgetItem->setCheckState(Qt::Unchecked);
            ui->sourcesTableWidget->setItem(iNewRowIndex, 1, pWidgetItem );
            ui->sourcesTableWidget->setItem(iNewRowIndex, 2, new QTableWidgetItem("No parser") );
        }
    }
}

void CCreateProjectDialog::getSourceList(QList<KotkaSource::SSourceData> &a_rSourcesDataList) const
{
    for( int iRow = 0
       ; ui->sourcesTableWidget->rowCount() > iRow
       ; ++iRow )
    {
        KotkaSource::SSourceData sSourceData;
        sSourceData.m_strName = ui->sourcesTableWidget->item(iRow, 0)->text();
        sSourceData.m_fReadOnly = (Qt::Checked == ui->sourcesTableWidget->item(iRow, 1)->checkState() );
        sSourceData.m_strParserName = ui->sourcesTableWidget->item(iRow, 2)->text();

        a_rSourcesDataList.append(sSourceData);
    }
}
