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

    QString getName() const;
    QDateTime getDeliveryDate() const;
    QDateTime getWritersDeadline() const;

public slots:
    virtual void accept();

private:
    bool validateInputData() const;
    bool validateProjectName() const;
    bool validateDeadlinesDates() const;
    bool validateClient() const;

    Ui::CCreateProjectDialog *ui;
};

#endif // CCREATEPROJECTDIALOG_H
