#ifndef CCLIENTSANDWRITERSDBMODEL_H
#define CCLIENTSANDWRITERSDBMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "cperson.h"

class CClientsAndWritersDbModel : public QAbstractTableModel
{
    Q_OBJECT
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
    virtual bool insertRows(int row, int count, const QModelIndex &parent);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);

signals:
    void contactWasCreated(KotkaSource::SContactData const &);
public slots:
    void append(QString a_strName);
    void addNewContactSlot(KotkaSource::SContactData const & a_rContactData);
    void remove(int a_iIndex);

private:
    QList<CPerson> m_aClientsAndWritesList;
};

#endif // CCLIENTSANDWRITERSDBMODEL_H
