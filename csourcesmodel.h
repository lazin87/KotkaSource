#ifndef CSOURCESMODEL_H
#define CSOURCESMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "isource.h"

class CSourcesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CSourcesModel(QObject * a_pParent = 0);
    ~CSourcesModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:
    QList<ISources *> m_aPtrsSourcesList;
};

#endif // CSOURCESMODEL_H
