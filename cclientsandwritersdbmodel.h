#ifndef CCLIENTSANDWRITERSDBMODEL_H
#define CCLIENTSANDWRITERSDBMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "cperson.h"

class CClientsAndWritersDbModel : public QAbstractTableModel
{
public:
    CClientsAndWritersDbModel(QObject * a_pParent = 0);
    ~CClientsAndWritersDbModel();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &a_Index, int a_iRole) const;
    virtual QVariant headerData(int a_iSection, Qt::Orientation a_orinetation, int a_iRole) const;
    virtual bool setData(const QModelIndex & a_iIndex, const QVariant & a_rValue, int a_iRole = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    void append(QString a_strName);
    void remove(int a_iIndex);


    static CPerson::EPersonPropertis mapToPersonProperty(int a_iColumnIndex);

private:
    QList<CPerson> m_aClientsAndWritesList;
};

#endif // CCLIENTSANDWRITERSDBMODEL_H
