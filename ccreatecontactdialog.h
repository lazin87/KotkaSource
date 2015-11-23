#ifndef CCREATECONTACTDIALOG_H
#define CCREATECONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class CCreateContactDialog;
}

class CCreateContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CCreateContactDialog(QWidget *parent = 0);
    ~CCreateContactDialog();

private:
    Ui::CCreateContactDialog *ui;
};

#endif // CCREATECONTACTDIALOG_H
