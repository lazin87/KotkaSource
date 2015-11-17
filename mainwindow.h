#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAbstractItemModel;
class QItemSelectionModel;
class QItemSelection;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setModel(QAbstractItemModel *a_pModel);

private slots:
    void selectionChangedSlot(const QItemSelection & /*newSelection*/, const QItemSelection & /*oldSelection*/ );
    void changeDeliveryDateSlot(const QDateTime &a_oNewDateTime);
    void changeCopyDeadlineSlot(QDateTime const & a_oNewDateTime);
    void changeNameSlot();

    void addProjectSlot();
    void onProjTreeContextMenu(const QPoint & a_rcPoint);

private:
    void createProjectTreeContextMenu();

    Ui::MainWindow *ui;

    QAction * m_pAddProjectAction;

};

#endif // MAINWINDOW_H
