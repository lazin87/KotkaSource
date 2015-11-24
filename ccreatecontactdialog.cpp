#include "ccreatecontactdialog.h"
#include "ui_ccreatecontactdialog.h"

#include <QAbstractItemModel>
#include <QDebug>

#include <QRegExp>

CCreateContactDialog::CCreateContactDialog(QWidget *parent, QString const & a_strName) :
    QDialog(parent),
    ui(new Ui::CCreateContactDialog),
    m_pAddressBookModel(0),
    m_fNameCanBeTheSame(false)
{
    ui->setupUi(this);
    ui->nameLineEdit->setText(a_strName);
}

CCreateContactDialog::CCreateContactDialog(QWidget *parent, const KotkaSource::SContactData &a_sContactData)
    : CCreateContactDialog(parent, a_sContactData.m_strName)
{
    ui->emailLineEdit->setText(a_sContactData.m_strEmail);
    ui->phoneLineEdit->setText(a_sContactData.m_strPhone);
    ui->isClientcheckBox->setChecked(a_sContactData.m_fIsClient);
    ui->isWriterCheckBox->setChecked(a_sContactData.m_fIsWriter);
    setWindowTitle("Edit contact");

    m_fNameCanBeTheSame = true;
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

bool CCreateContactDialog::validateInputData() const
{
    bool fResult = true;

    fResult &= validateClientName();
    fResult &= validateEmail();
    fResult &= validatePhone();
    fResult &= m_fNameCanBeTheSame || checkNameIfUnique();
    fResult &= validateAddress();

    return fResult;
}

bool CCreateContactDialog::validateClientName() const
{
    bool fResult = true;
    ui->nameLineEdit->setText( ui->nameLineEdit->text().simplified() );

    QRegExp regExp("^[a-zA-Z]\\w*(?:\\s\\w*)*$");
    fResult = (-1 != regExp.indexIn(ui->nameLineEdit->text() ) );

    ui->nameLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    return fResult;
}

bool CCreateContactDialog::validateEmail() const
{
    bool fResult = true;
    ui->emailLineEdit->setText( ui->emailLineEdit->text().simplified() );

    QRegExp regExp("^\\w+@\\w+(?:\\.\\w{2,})+$");
    fResult = (-1 != regExp.indexIn(ui->emailLineEdit->text() ) );

    ui->emailLineEdit->setStyleSheet(
                fResult ? "" : "QLineEdit { background-color : red; }"
                          );

    return fResult;
}

bool CCreateContactDialog::validatePhone() const
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

    return fResult;
}

bool CCreateContactDialog::checkNameIfUnique() const
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
            qWarning() << "checkNameIfUnique::Contact exists";
        }
    }
    else
    {
        qWarning() << "checkNameIfUnique::some name error";
    }

    return fResult;
}

bool CCreateContactDialog::validateAddress() const
{

    bool fResult = true;
    ui->addressPlainTextEdit->setPlainText( ui->addressPlainTextEdit->toPlainText() );
    fResult = (KotkaSource::ADDRESS_LENGTH >= ui->addressPlainTextEdit->toPlainText().length() );

    ui->addressPlainTextEdit->setStyleSheet(
                fResult ? "" : "QPlainTextEdit { background-color : red; }"
                          );

    return fResult;
}
