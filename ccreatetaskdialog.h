#ifndef CCREATETASKDIALOG_H
#define CCREATETASKDIALOG_H

#include <QDialog>

#include "commonddefs.h"

class QAbstractItemModel;

namespace Ui {
class CCreateTaskDialog;
}

class CCreateTaskDialog : public QDialog
{
    Q_OBJECT

public:
    CCreateTaskDialog( KotkaSource::SProjectData const * a_pParentProjectData
                     , QWidget *parent = 0);
    CCreateTaskDialog( const KotkaSource::SProjectData *a_pParentProjectData
                     , KotkaSource::STaskData const * a_pTaskRoot
                     , QWidget *parent);

    ~CCreateTaskDialog();

    void getData(KotkaSource::STaskData & a_rTaskData) const;
    void setAddressDbToCompleter(QAbstractItemModel * a_pModel);

public slots:
    virtual void accept();

private:
    bool validateInputData() const;
    bool validateProjectName() const;
    bool validateDeadlinesDates() const;

    void initEditOption();
    void lockUneditableFields();
    void fillInPrjInformation(KotkaSource::STaskData const & a_rTaskData);

    Ui::CCreateTaskDialog *ui;

    QString m_strParentName;
    KotkaSource::SProjectData const * m_pParentProjectData;
    KotkaSource::STaskData const * m_pRootTask;
};

#endif // CCREATETASKDIALOG_H
