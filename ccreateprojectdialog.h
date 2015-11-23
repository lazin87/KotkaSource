#ifndef CCREATEPROJECTDIALOG_H
#define CCREATEPROJECTDIALOG_H

#include <QDialog>

#include "commonddefs.h"

class QAbstractItemModel;
class QCompleter;
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

    void getData(KotkaSource::SProjectData & a_rProjectData) const;
    void setAddressDbToCompleter(QAbstractItemModel * a_pModel);

    QString getClientName() const;

public slots:
    virtual void accept();
    void selectedClientChangedSlot(const QModelIndex & a_rModelIndex);

protected:
    void setErrorMsg(QString const & a_strErrorMsg) const;

private:
    void setEmail(const QModelIndex &a_rModelIndex);
    void setPhone(const QModelIndex &a_rModelIndex);
    void setAddress(const QModelIndex &a_rModelIndex);

    bool validateInputData() const;
    bool validateProjectName() const;
    bool validateDeadlinesDates() const;
    bool validateClient() const;

    Ui::CCreateProjectDialog *ui;
};

#endif // CCREATEPROJECTDIALOG_H
