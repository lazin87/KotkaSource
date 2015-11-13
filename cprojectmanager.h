#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H

#include <QObject>
#include <QList>
#include <QStandardItemModel>

class IProject;

class CProjectManager : public QObject
{
    Q_OBJECT
public:
    CProjectManager(QObject * a_pParent = 0);
    ~CProjectManager();

    QStandardItemModel * getModel() const;

private:
    void prepareModel();

    QStandardItemModel m_oModel;
    QList<IProject *> m_pProjetsList;
};

#endif // CPROJECTMANAGER_H
