#ifndef CPROJECTSMODEL_H
#define CPROJECTSMODEL_H

#include <QAbstractTableModel>

class CProjectsModel : public  QAbstractTableModel
{
    Q_OBJECT
public:
    CProjectsModel(QObject * a_pParent);
    ~CProjectsModel();

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex() ) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // CPROJECTSMODEL_H
