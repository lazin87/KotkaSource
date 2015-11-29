#ifndef CSOURCESMODEL_H
#define CSOURCESMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "isource.h"

class CSourcesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CSourcesModel(QString const & a_strModelName = "", QObject * a_pParent = 0);
    ~CSourcesModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

public slots:
    void addNewSource(QString const & a_strName, bool a_fReadOnly);
    void removeSourceSlot(QModelIndex const & a_rModelIndex);

private:
    void clearSourcesList();
    void prepareInOutFolders();
    void makeFileNameUnique(QString & a_rFileName);

    QString m_strName;
    QList<ISource *> m_aPtrsSourcesList;
};

#endif // CSOURCESMODEL_H
