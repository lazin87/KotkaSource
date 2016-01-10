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
    explicit CCreateProjectDialog( QWidget *parent
                                 , QAbstractItemModel * a_pAddressBook
                                 , const KotkaSource::SProjectData * a_pRootPrjData = 0
                                 , bool a_fEdit = false
                                 );
    ~CCreateProjectDialog();

    QString getName() const;
    QDateTime getDeliveryDate() const;
    QDateTime getWritersDeadline() const;

    void getProjectData(KotkaSource::SProjectData & a_rProjectData) const;
    void setAddressDbModel(QAbstractItemModel * a_pModel);
    void getSourceList(QList<KotkaSource::SSourceData> & a_rSourcesDataList) const;

    QString getClientName() const;

    int exec();

public slots:
    virtual void accept();
    void clientAddSlot();
    void clientEditSlot();
    void clientNameWasChangedSlot(QString const & a_rNewName);
    void sourceAddSlot();
    void sourceRemoveSlot();

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
    void fillInPrjInformation(KotkaSource::SProjectData const & a_rProjectData);
    void lockUneditableFields();

    bool validateInputData() const;
    bool validateProjectName() const;
    bool validateDeadlinesDates() const;
    bool validateClient() const;

    QModelIndex findClientIndex(const QString &a_rStrName) const;
    bool checkIfClient(QModelIndex const & a_rIndex) const;

    void setupSourcesTable();
    void addNewEntriesToSourcesTable(const QStringList &a_strPathList);

    void initEditOption();

    Ui::CCreateProjectDialog *ui;
    KotkaSource::SProjectData const * m_pRootProjectData;
    QAbstractItemModel * m_pContactDbModel;
    bool m_fHasEditPrj;
};

#endif // CCREATEPROJECTDIALOG_H
