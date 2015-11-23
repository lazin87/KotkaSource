#ifndef CCREATECONTACTDIALOG_H
#define CCREATECONTACTDIALOG_H

#include <QDialog>

#include "commonddefs.h"

class QAbstractTableModel;

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
    void setAddressBookModel(QAbstractTableModel *a_pAddressBookModel);

public slots:
    virtual void accept();

private:
    bool validateInputData() const;
    bool validateClientName() const;
    bool validateEmail() const;
    bool validatePhone() const;
    bool checkNameIfUnique() const;

    Ui::CCreateContactDialog *ui;
    QAbstractTableModel * m_pAddressBookModel;
};

#endif // CCREATECONTACTDIALOG_H
