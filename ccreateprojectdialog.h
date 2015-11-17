#ifndef CCREATEPROJECTDIALOG_H
#define CCREATEPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class CCreateProjectDialog;
}

class CCreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CCreateProjectDialog(QWidget *parent = 0);
    ~CCreateProjectDialog();

private:
    Ui::CCreateProjectDialog *ui;
};

#endif // CCREATEPROJECTDIALOG_H
