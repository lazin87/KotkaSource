#include "cclientsandwritersdbmodel.h"

#include <QDebug>

CClientsAndWritersDbModel::CClientsAndWritersDbModel(QObject *a_pParent)
    : QAbstractTableModel(a_pParent)
{

}

CClientsAndWritersDbModel::~CClientsAndWritersDbModel()
{

}



int CClientsAndWritersDbModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_aClientsAndWritesList.count();
}

int CClientsAndWritersDbModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return CPerson::getPropertyCount();
}

QVariant CClientsAndWritersDbModel::data(const QModelIndex &index, int role) const
{
}

void CClientsAndWritersDbModel::append(QString a_strName)
{
    m_aClientsAndWritesList.append(CPerson(a_strName) );
}

void CClientsAndWritersDbModel::remove(int a_iIndex)
{
    if( (!m_aClientsAndWritesList.empty() ) && (0 <= a_iIndex) && (m_aClientsAndWritesList.count() > a_iIndex) )
    {
        m_aClientsAndWritesList.removeAt(a_iIndex);
    }
    else
    {
        qDebug() << "CClientsAndWritersDbModel::remove(): index out of bound";
    }
}
