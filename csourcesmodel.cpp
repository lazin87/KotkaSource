#include "csourcesmodel.h"

CSourcesModel::CSourcesModel(QObject *a_pParent)
    :QAbstractTableModel(a_pParent)
{

}



int CSourcesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_aPtrsSourcesList.count();
}

int CSourcesModel::columnCount(const QModelIndex &parent) const
{
}

QVariant CSourcesModel::data(const QModelIndex &index, int role) const
{
}
