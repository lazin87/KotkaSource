#include "cprojectsmodel.h"

CProjectsModel::CProjectsModel(QObject *a_pParent)
{

}

CProjectsModel::~CProjectsModel()
{

}



int CProjectsModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}

int CProjectsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CProjectsModel::data(const QModelIndex &index, int role) const
{
    if(Qt::DisplayRole == role)
    {
        return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() + 1);
    }

    return QVariant();
}
