#include "ccreatecontactdialog.h"
#include "ui_ccreatecontactdialog.h"

#include <QAbstractTableModel>

CCreateContactDialog::CCreateContactDialog(QWidget *parent, QString const & a_strName) :
    QDialog(parent),
    ui(new Ui::CCreateContactDialog),
    m_pAddressBookModel(0)
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

void CCreateContactDialog::setAddressBookModel(QAbstractTableModel *a_pAddressBookModel)
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

    return fResult;
}

bool CCreateContactDialog::validateClientName() const
{
    bool fResult = true;
    return fResult;
}

bool CCreateContactDialog::validateEmail() const
{
    bool fResult = true;
    return fResult;
}

bool CCreateContactDialog::validatePhone() const
{
    bool fResult = true;
    return fResult;
}

bool CCreateContactDialog::checkNameIfUnique() const
{
    bool fResult = true;

    fResult = (0 != m_pAddressBookModel);

    if(fResult)
    {
        // implement matching function!!
#error implement matching function!!
       // m_pAddressBookModel->match()
    }
    return fResult;
}
