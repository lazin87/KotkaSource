#include "cclientsandwritersdbmodel.h"

#include <QDebug>

#include "commonddefs.h"

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

    return CPersonPropertis::count();
}

// PRZEMYSLEC TA FUNKCJE!!
QVariant CClientsAndWritersDbModel::data(const QModelIndex &a_Index, int a_iRole) const
{
    switch(a_iRole)
    {
    case Qt::EditRole:
    {
        // used for autocompletion
        return m_aClientsAndWritesList[a_Index.row() ].getPropertyData( CPersonPropertis::mapToPersonProperty(a_Index.column() ) );
    }
    case Qt::DisplayRole:
    {
        if(  (CPersonPropertis::eIsClient == CPersonPropertis::mapToPersonProperty(a_Index.column() ) )
          || (CPersonPropertis::eIsWriter == CPersonPropertis::mapToPersonProperty(a_Index.column() ) )
          )
        {
            return QVariant();
        }

        return m_aClientsAndWritesList[a_Index.row() ].getPropertyData( CPersonPropertis::mapToPersonProperty(a_Index.column() ) );
    }
    case Qt::CheckStateRole:
    {
        if(  (CPersonPropertis::eIsClient == CPersonPropertis::mapToPersonProperty(a_Index.column() ) )
          || (CPersonPropertis::eIsWriter == CPersonPropertis::mapToPersonProperty(a_Index.column() ) )
          )
        {
            bool fValue = m_aClientsAndWritesList[a_Index.row() ].getPropertyData( CPersonPropertis::mapToPersonProperty(a_Index.column() ) ).toBool();
            return fValue ? Qt::Checked : Qt::Unchecked;
        }
        else
        {
            return QVariant();
        }
    }
    case KotkaSource::ObjectEmailRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].strEmail();
    }
    case KotkaSource::ObjectPhoneRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].strPhone();
    }
    case KotkaSource::ObjectAddressRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].strAddress();
    }
    case KotkaSource::ContactIsClientRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].isClient();
    }
    case KotkaSource::ContactIsWriterRole:
    {
        return m_aClientsAndWritesList[a_Index.row() ].isWriter();
    }
    case KotkaSource::ReadContactDataRole:
    {
        return QVariant::fromValue(m_aClientsAndWritesList[a_Index.row() ].getContactData() );
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
            CPersonPropertis::EPersonPropertis propertyIndex = CPersonPropertis::mapToPersonProperty(a_iSection);
            return CPersonPropertis::s_aPropertisLabels[propertyIndex];
        }

        if(Qt::Vertical == a_orinetation)
        {
            return a_iSection;
        }
    }

    return QVariant();
}

bool CClientsAndWritersDbModel::setData(const QModelIndex &a_iIndex, const QVariant &a_rValue, int a_iRole)
{
    if(Qt::EditRole == a_iRole)
    {
        m_aClientsAndWritesList[a_iIndex.row() ].setPropertyData( CPersonPropertis::mapToPersonProperty(a_iIndex.column() )
                                                                , a_rValue
                                                                );

        emit dataChanged(a_iIndex, a_iIndex);
    }
    else if(Qt::CheckStateRole == a_iRole)
    {
        m_aClientsAndWritesList[a_iIndex.row() ].setPropertyData( CPersonPropertis::mapToPersonProperty(a_iIndex.column() )
                                                                , a_rValue
                                                                );
    }

    return true;
}

Qt::ItemFlags CClientsAndWritersDbModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags outFlags = Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;

    if(  (CPersonPropertis::eIsClient == CPersonPropertis::mapToPersonProperty(index.column() ) )
      || (CPersonPropertis::eIsWriter == CPersonPropertis::mapToPersonProperty(index.column() ) )
      )
    {
        outFlags |= Qt::ItemIsUserCheckable;
    }

    return outFlags;
}

void CClientsAndWritersDbModel::append(QString a_strName)
{
    qDebug() << "CClientsAndWritersDbModel::append()";
    m_aClientsAndWritesList.append(CPerson(a_strName) );
}

void CClientsAndWritersDbModel::addNewContactSlot(const KotkaSource::SContactData &a_rContactData)
{
    qDebug() << "CClientsAndWritersDbModel::append()";
    m_aClientsAndWritesList.append(CPerson(a_rContactData) );
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


bool CClientsAndWritersDbModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    endInsertRows();
}

bool CClientsAndWritersDbModel::removeRows(int row, int count, const QModelIndex &parent)
{
}
