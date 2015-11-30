#ifndef CCREATEPROJECTDIALOG_H
#define CCREATEPROJECTDIALOG_H

#include <QDialog>

#include "commonddefs.h"
#include "csourcesmodel.h"

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

    void getProjectData(KotkaSource::SProjectData & a_rProjectData) const;
    void getSourcesModel(CSourcesModel & a_rSorucesModel) const;
    void setAddressDbToCompleter(QAbstractItemModel * a_pModel);

    QString getClientName() const;

public slots:
    virtual void accept();
    void clientAddSlot();
    void clientEditSlot();
    void clientNameWasChangedSlot(QString const & a_rNewName);
    void sourceAddSlot();

signals:
    void addNewContact(KotkaSource::SContactData const & a_crContactData);
    void editContact(KotkaSource::SContactData const & a_crContactData);

protected:
    void setErrorMsg(QString const & a_strErrorMsg) const;

private:
    void setEmail(const QModelIndex &a_rModelIndex);
    void setPhone(const QModelIndex &a_rModelIndex);
    void setAddress(const QModelIndex &a_rModelIndex);
    void fillInClientInformation(KotkaSource::SContactData const & a_rContactData);
    void fillInClientInformation(const QModelIndex &a_rModelIndex);

    bool validateInputData() const;
    bool validateProjectName() const;
    bool validateDeadlinesDates() const;
    bool validateClient() const;

    QModelIndex findClientIndex(const QString &a_rStrName) const;
    bool checkIfClient(QModelIndex const & a_rIndex) const;

    void setupSourcesTable();
    void addNewEntriesToSourcesTable(const QStringList &a_strPathList);

    Ui::CCreateProjectDialog *ui;
    CSourcesModel m_oSourcesModel;
};

#endif // CCREATEPROJECTDIALOG_H
