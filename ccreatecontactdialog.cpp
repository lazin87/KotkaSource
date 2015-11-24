#include "ccreatecontactdialog.h"
#include "ui_ccreatecontactdialog.h"

#include <QAbstractItemModel>
#include <QDebug>

#include <QRegExp>

CCreateContactDialog::CCreateContactDialog(QWidget *parent, QString const & a_strName) :
    QDialog(parent),
    ui(new Ui::CCreateContactDialog),
    m_pAddressBookModel(0),
    m_fDisableNameValidation(false),
    m_strLastErrors("")
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(a_strName);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");
}

CCreateContactDialog::CCreateContactDialog(QWidget *parent, const KotkaSource::SContactData &a_sContactData)
    : CCreateContactDialog(parent, a_sContactData.m_strName)
{
    ui->emailLineEdit->setText(a_sContactData.m_strEmail);
    ui->phoneLineEdit->setText(a_sContactData.m_strPhone);
    ui->addressPlainTextEdit->setPlainText(a_sContactData.m_strAddress);
    ui->isClientcheckBox->setChecked(a_sContactData.m_fIsClient);
    ui->isWriterCheckBox->setChecked(a_sContactData.m_fIsWriter);
    setWindowTitle("Edit contact");

    m_fDisableNameValidation = true;
    ui->nameLineEdit->setDisabled(true);
}

CCreateContactDialog::~CCreateContactDialog()
{
    delete ui;
}

void CCreateContactDialog::getContactData(KotkaSource::SContactData &a_rContactData) const
{
    a_rContactData.m_strEmail = ui->emailLineEdit->text();
    a_rContactData.m_strName = ui->nameLineEdit->text();
    a_rContactData.m_strPhone = ui->phoneLineEdit->text();
    a_rContactData.m_strAddress = ui->addressPlainTextEdit->toPlainText();
    a_rContactData.m_fIsWriter = ui->isWriterCheckBox->isChecked();
    a_rContactData.m_fIsClient = ui->isClientcheckBox->isChecked();
}

void CCreateContactDialog::setAddressBookModel(QAbstractItemModel *a_pAddressBookModel)
{
    m_pAddressBookModel = a_pAddressBookModel;
}

void CCreateContactDialog::accept()
{
    if(validateInputData() )
    {
        QDialog::accept();
    }
}

void CCreateContactDialog::displayLastErrors() const
{
    ui->errorLabel->setText(m_strLastErrors);
}

void CCreateContactDialog::resetLastErrors()
{
    m_strLastErrors = "";
}

void CCreateContactDialog::addError(const QString &a_strErrorMsg)
{
    if(false == m_strLastErrors.isEmpty() )
    {
        m_strLastErrors += "\n";
    }

    m_strLastErrors += a_strErrorMsg;
}

bool CCreateContactDialog::validateInputData()
{
    bool fResult = true;

    resetLastErrors();

    fResult &= m_fDisableNameValidation || validateClientName();
    fResult &= validateEmail();
    fResult &= validatePhone();
    fResult &= m_fDisableNameValidation || checkNameIfUnique();
    fResult &= validateAddress();

    displayLastErrors();

    return fResult;
}

bool CCreateContactDialog::validateClientName()
{
    bool fResult = true;
    ui->nameLineEdit->setText( ui->nameLineEdit->text().simplified() );

    QRegExp regExp("^[a-zA-Z]\\w*(?:\\s\\w*)*$");
    fResult = (-1 != regExp.indexIn(ui->nameLineEdit->text() ) );

    ui->nameLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    addError("Invalid client name.");

    return fResult;
}

bool CCreateContactDialog::validateEmail()
{
    bool fResult = true;
    ui->emailLineEdit->setText( ui->emailLineEdit->text().simplified() );

    QRegExp regExp("^\\w+@\\w+(?:\\.\\w{2,})+$");
    fResult = (-1 != regExp.indexIn(ui->emailLineEdit->text() ) );

    ui->emailLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    addError("Invalid client email.");

    return fResult;
}

bool CCreateContactDialog::validatePhone()
{
    bool fResult = true;
    QString strTemp = ui->phoneLineEdit->text().simplified();
    strTemp.replace( " ", "");
    strTemp.replace("-", "");
    ui->phoneLineEdit->setText(strTemp);

    QRegExp regExp("^\\+?\\d+$");
    fResult = (-1 != regExp.indexIn(ui->phoneLineEdit->text() ) );
    ui->phoneLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    addError("Invalid client phone.");

    return fResult;
}

bool CCreateContactDialog::checkNameIfUnique()
{
    bool fResult = true;

    fResult = (0 != m_pAddressBookModel);

    if(fResult)
    {
        QModelIndex startIndex = m_pAddressBookModel->index(0, CPersonPropertis::toInt(CPersonPropertis::eName) );
        fResult &= m_pAddressBookModel->match( startIndex
                                             , Qt::DisplayRole
                                             , ui->nameLineEdit->text()
                                             , 1
                                             , Qt::MatchFixedString
                                             ).empty();

        if(!fResult)
        {
            addError("Client already exist.");
        }
    }
    else
    {
        addError("Address book was not registered.");
    }

    ui->nameLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    return fResult;
}

bool CCreateContactDialog::validateAddress()
{

    bool fResult = true;
    ui->addressPlainTextEdit->setPlainText( ui->addressPlainTextEdit->toPlainText() );
    fResult = (KotkaSource::ADDRESS_LENGTH >= ui->addressPlainTextEdit->toPlainText().length() );

    ui->addressPlainTextEdit->setStyleSheet(
                fResult ? "" : "QPlainTextEdit { background-color : red; }"
                          );

    if(!fResult)
    {
        addError( QString("Address execeds %1 characters.").arg(KotkaSource::ADDRESS_LENGTH) );
    }

        return fResult;
}
