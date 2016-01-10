#include "ccreateprojectdialog.h"
#include "ui_ccreateprojectdialog.h"

#include <QCompleter>
#include <QDebug>
#include <QFileDialog>
#include <QDir>

#include "ccreatecontactdialog.h"

CCreateProjectDialog::CCreateProjectDialog(QWidget *parent, const KotkaSource::SProjectData *a_pRootPrjData, bool a_fEdit) :
    QDialog(parent),
    ui(new Ui::CCreateProjectDialog),
    m_pRootProjectData(a_pRootPrjData),
    m_pContactDbModel(0),
    m_fHasEditPrj(a_fEdit)
{
    ui->setupUi(this);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
    ui->clientErrorLabel->setStyleSheet("QLabel { color : red; }");

    setupSourcesTable();

    if(a_fEdit)
    {
        initEditOption();
    }
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
    if(m_fHasEditPrj)
    {
        a_rProjectData.m_strName = noChange<QString>();
        a_rProjectData.m_oDateTimeDelivery = (ui->deliveryDateTimeEdit->dateTime() == m_pRootProjectData->m_oDateTimeDelivery) ?
                    noChange<QDateTime>() : ui->deliveryDateTimeEdit->dateTime();
        a_rProjectData.m_oDateTimeWriterDeadline = (ui->writersDeadlineDateTimeEdit->dateTime() == m_pRootProjectData->m_oDateTimeWriterDeadline) ?
                    noChange<QDateTime>() : ui->writersDeadlineDateTimeEdit->dateTime();
        a_rProjectData.m_strClientName = (ui->clientComboBox->currentText() == m_pRootProjectData->m_strClientName) ?
                    noChange<QString>() : ui->clientComboBox->currentText();
        a_rProjectData.m_strParentName = noChange<QString>();
    }
    else
    {
        a_rProjectData.m_strName = ui->projectNamelineEdit->text();
        a_rProjectData.m_oDateTimeDelivery = ui->deliveryDateTimeEdit->dateTime();
        a_rProjectData.m_oDateTimeWriterDeadline = ui->writersDeadlineDateTimeEdit->dateTime();
        a_rProjectData.m_strClientName = ui->clientComboBox->currentText();
        a_rProjectData.m_strParentName = (0 == m_pRootProjectData) ? "" : m_pRootProjectData->m_strName;
    }
}

void CCreateProjectDialog::setAddressDbModel(QAbstractItemModel *a_pModel)
{
    if(0 != a_pModel )
    {
        m_pContactDbModel = a_pModel;
        ui->clientComboBox->setModel(m_pContactDbModel);
    }
    else
    {
        qWarning() << "CCreateProjectDialog::setAddressDbToCompleter: can not set model";
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
    oCreateContactDialog.setAddressBookModel(m_pContactDbModel );

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
    if(false == ui->clientComboBox->currentText().isEmpty() && (0 != m_pContactDbModel) )
    {
        QModelIndex oClientIndex = findClientIndex(ui->clientComboBox->currentText() );

        if(oClientIndex.isValid() )
        {
            QVariant rawData = m_pContactDbModel->data( oClientIndex,
                                                        KotkaSource::ReadContactDataRole
                                                        );
            KotkaSource::SContactData clientContactData = rawData.value<KotkaSource::SContactData>();
            CCreateContactDialog oEditContactDialog(this, clientContactData);

            if(QDialog::Accepted == oEditContactDialog.exec() )
            {
                KotkaSource::SContactData sContactData;
                oEditContactDialog.getContactData(sContactData);

                fillInClientInformation(sContactData);
                m_pContactDbModel->setData( oClientIndex
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

void CCreateProjectDialog::sourceRemoveSlot()
{
    int iNumberOfRemovedRows = 0;
    QList<QTableWidgetSelectionRange> selectionRanges = ui->sourcesTableWidget->selectedRanges();
    foreach(QTableWidgetSelectionRange selectionRange, selectionRanges)
    {
        int iFirstItem = selectionRange.topRow() - iNumberOfRemovedRows;
        for( int iRemovedItems = 0//selectionRange.topRow()
           ; selectionRange.rowCount() > iRemovedItems
           ; ++iRemovedItems )
        {
            ui->sourcesTableWidget->removeRow(iFirstItem);
        }

        iNumberOfRemovedRows += selectionRange.rowCount();
    }
}

void CCreateProjectDialog::setEmail(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() && (0 != m_pContactDbModel) )
    {
        QVariant rawVal = m_pContactDbModel->data( a_rModelIndex
                                                   , KotkaSource::ObjectEmailRole
                                                   );
        strTemp = rawVal.toString();
    }
    ui->emailDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setPhone(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() && (0 != m_pContactDbModel) )
    {
        QVariant rawVal = m_pContactDbModel->data( a_rModelIndex
                                                   , KotkaSource::ObjectPhoneRole
                                                   );
        strTemp = rawVal.toString();
    }
    ui->phoneDispLabel->setText(strTemp);
}

void CCreateProjectDialog::setAddress(const QModelIndex &a_rModelIndex)
{
    QString strTemp = "";
    if(a_rModelIndex.isValid() && (0 != m_pContactDbModel) )
    {
        QVariant rawVal = m_pContactDbModel->data( a_rModelIndex
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

void CCreateProjectDialog::fillInPrjInformation(const KotkaSource::SProjectData &a_rProjectData)
{
    ui->projectNamelineEdit->setText(a_rProjectData.m_strName);
    ui->deliveryDateTimeEdit->setDateTime(a_rProjectData.m_oDateTimeDelivery);
    ui->writersDeadlineDateTimeEdit->setDateTime(a_rProjectData.m_oDateTimeWriterDeadline);
    ui->clientComboBox->setCurrentText(a_rProjectData.m_strClientName);
}

void CCreateProjectDialog::lockUneditableFields()
{
    ui->projectNamelineEdit->setEnabled(false);
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
    if(0 != m_pContactDbModel)
    {
        QModelIndex oStartIndex = m_pContactDbModel->index(0, CPersonPropertis::toInt(CPersonPropertis::eName) );
        QModelIndexList oModelIndexList = m_pContactDbModel->match( oStartIndex
                                                                    , Qt::DisplayRole
                                                                    , a_rStrName
                                                                    , 1
                                                                    , Qt::MatchFixedString
                                                                    );
        return  (oModelIndexList.isEmpty() ) ? QModelIndex() : oModelIndexList[0];
    }
    else
    {
        qWarning() << "CCreateProjectDialog::findClientIndex: no Db was set";
        return QModelIndex();
    }
}

bool CCreateProjectDialog::checkIfClient(const QModelIndex &a_rIndex) const
{
    if(0 != m_pContactDbModel)
    {
        QVariant rawVal = m_pContactDbModel->data( a_rIndex
                                                   , KotkaSource::ContactIsClientRole
                                                   );
        return rawVal.toBool();
    }
    else
    {
        qWarning() << "CCreateProjectDialog::checkIfClient: no Db was set";
        return false;
    }
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
            ui->sourcesTableWidget->setItem(iNewRowIndex, 2, new QTableWidgetItem("") );
        }
    }
}

void CCreateProjectDialog::initEditOption()
{
    if(0 != m_pRootProjectData)
    {
        lockUneditableFields();
        fillInPrjInformation(*m_pRootProjectData);
        this->setWindowTitle("Edit project");
    }
    else
    {
        qWarning() << "CCreateProjectDialog::initEditOption(): Project was not set!";
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
