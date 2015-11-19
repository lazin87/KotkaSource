#ifndef CCREATETASKDIALOG_H
#define CCREATETASKDIALOG_H

#include <QDialog>

#include "commonddefs.h"

struct KotkaSource::SProjectData;

namespace Ui {
class CCreateTaskDialog;
}

class CCreateTaskDialog : public QDialog
{
    Q_OBJECT

public:
    CCreateTaskDialog( KotkaSource::SProjectData const * a_pParentProjectData
                     , QWidget *parent = 0);

    ~CCreateTaskDialog();

private:
    Ui::CCreateTaskDialog *ui;

    KotkaSource::SProjectData const * m_pParentProjectData;
};

#endif // CCREATETASKDIALOG_H
