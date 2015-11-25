#ifndef CSOURCESMODEL_H
#define CSOURCESMODEL_H

#include <QAbstractTableModel>

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
};

#endif // CSOURCESMODEL_H
