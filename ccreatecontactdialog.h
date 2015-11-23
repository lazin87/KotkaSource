#ifndef CCREATECONTACTDIALOG_H
#define CCREATECONTACTDIALOG_H

#include <QDialog>

#include "commonddefs.h"

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

private:
    Ui::CCreateContactDialog *ui;
};

#endif // CCREATECONTACTDIALOG_H
