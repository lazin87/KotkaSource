#ifndef CCLIENTSANDWRITERSDBMODEL_H
#define CCLIENTSANDWRITERSDBMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "cperson.h"

class CClientsAndWritersDbModel : public QAbstractTableModel
{
public:
    CClientsAndWritersDbModel(QObject * a_pParent);
    ~CClientsAndWritersDbModel();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    void append(QString a_strName);
    void remove(int a_iIndex);

private:
    QList<CPerson> m_aClientsAndWritesList;
};

#endif // CCLIENTSANDWRITERSDBMODEL_H
