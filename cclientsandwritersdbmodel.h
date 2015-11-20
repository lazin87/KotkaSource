#ifndef CCLIENTSANDWRITERSDBMODEL_H
#define CCLIENTSANDWRITERSDBMODEL_H

#include <QAbstractTableModel>

class CClientsAndWritersDbModel : public QAbstractTableModel
{
public:
    CClientsAndWritersDbModel();
    ~CClientsAndWritersDbModel();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // CCLIENTSANDWRITERSDBMODEL_H
