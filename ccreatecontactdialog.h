#ifndef CCREATECONTACTDIALOG_H
#define CCREATECONTACTDIALOG_H

#include <QDialog>

#include "commonddefs.h"

class QAbstractItemModel;

namespace Ui {
class CCreateContactDialog;
}

class CCreateContactDialog : public QDialog
{
    Q_OBJECT

public:
    CCreateContactDialog(QWidget *parent, const QString &a_strName = "");
    CCreateContactDialog(QWidget *parent, const KotkaSource::SContactData &a_sContactData);
    ~CCreateContactDialog();

    void getContactData(KotkaSource::SContactData & a_rContactData) const;
    void setAddressBookModel(QAbstractItemModel *a_pAddressBookModel);

public slots:
    virtual void accept();

private:
    void displayLastErrors() const;
    void resetLastErrors();
    void addError(QString const & a_strErrorMsg);

    bool validateInputData();
    bool validateClientName();
    bool validateEmail();
    bool validatePhone();
    bool checkNameIfUnique();
    bool validateAddress();

    Ui::CCreateContactDialog *ui;
    QAbstractItemModel * m_pAddressBookModel;
    bool m_fDisableNameValidation;
    QString m_strLastErrors;
};

#endif // CCREATECONTACTDIALOG_H
