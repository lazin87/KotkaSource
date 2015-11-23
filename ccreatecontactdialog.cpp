#include "ccreatecontactdialog.h"
#include "ui_ccreatecontactdialog.h"

CCreateContactDialog::CCreateContactDialog(QWidget *parent, QString const & a_strName) :
    QDialog(parent),
    ui(new Ui::CCreateContactDialog)
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
