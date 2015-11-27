#include "csourcesmodel.h"

CSourcesModel::CSourcesModel(QObject *a_pParent)
    :QAbstractTableModel(a_pParent)
{

}

CSourcesModel::~CSourcesModel()
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

void CSourcesModel::addNewSource(const QString &a_strName, bool a_fReadOnly)
{

}
