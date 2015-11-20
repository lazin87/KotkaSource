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

QVariant CClientsAndWritersDbModel::data(const QModelIndex &a_Index, int a_iRole) const
{
    switch(a_iRole)
    {
    case Qt::DisplayRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].getPropertyData( mapToPersonProperty(a_Index.column() ) );
    }

    default:
        return QVariant();
    }
}

QVariant CClientsAndWritersDbModel::headerData(int a_iSection, Qt::Orientation a_orinetation, int a_iRole) const
{
    if(Qt::DisplayRole == a_iRole)
    {
        if(Qt::Horizontal == a_orinetation)
        {
            CPerson::EPersonPropertis propertyIndex = mapToPersonProperty(a_iSection);
            return CPerson::s_aPropertisLabels[propertyIndex];
        }

        if(Qt::Vertical == a_orinetation)
        {
            return a_iSection;
        }
    }

    return QVariant();
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

CPerson::EPersonPropertis CClientsAndWritersDbModel::mapToPersonProperty(int a_iColumnIndex)
{
    CPerson::EPersonPropertis eResultPropertis = CPerson::ePP_Invalid;
    if( (CPerson::ePP_First <= a_iColumnIndex) && (CPerson::ePP_NumberOfPropertis > a_iColumnIndex) )
    {
        eResultPropertis = static_cast<CPerson::EPersonPropertis>(a_iColumnIndex);
    }

    return eResultPropertis;
}
