#include "iproject.h"

#include <QDebug>

IProject::IProject(QString a_strName)
    : QStandardItem(a_strName)
//    , m_sData()
{
//    m_sData.m_strName = a_strName;
//    m_sData.m_oDateTimeDelivery = QDateTime();
//    m_sData.m_oDateTimeWriterDeadline = QDateTime();
}

IProject::~IProject()
{

}

bool IProject::isLeaf() const
{
    return false;
}

//QDateTime IProject::deadlineDelivery() const
//{
//    QDateTime oOutDateTime = m_sData.m_oDateTimeDelivery;

//    if(false == oOutDateTime.isValid() )
//    {
//        QStandardItem * pParentItem = parent();

//        if( 0 != pParentItem )
//        {
//            oOutDateTime = pParentItem->data(KotkaSource::DeliveryDateRole).toDateTime();

//            if(false == oOutDateTime.isValid() )
//            {
//                qWarning("CProject::deadlineDelivery(): invalid");
//            }
//        }
//    }

//    return oOutDateTime;
//}

//void IProject::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
//{
//    m_sData.m_oDateTimeDelivery = a_rDeadlineDelivery;
//}

//QDateTime IProject::deadlineCopywriters() const
//{
//    QDateTime oOutDateTime = m_sData.m_oDateTimeWriterDeadline;

//    if(false == oOutDateTime.isValid() )
//    {
//        QStandardItem * pParentItem = parent();

//        if( 0 != pParentItem )
//        {
//            oOutDateTime = pParentItem->data(KotkaSource::WritersDeadlineDateRole).toDateTime();

//            if(false == oOutDateTime.isValid() )
//            {
//                qWarning("CProject::deadlineDelivery(): invalid");
//            }
//        }
//    }

//    return oOutDateTime;
//}

//void IProject::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
//{
//    m_sData.m_oDateTimeWriterDeadline = a_rDeadlineCopywriters;
//}

QVariant IProject::data(int a_iRole) const
{
    switch(a_iRole)
    {

    case KotkaSource::ProjectDescDispRole:
    {
        QString strData = "Name: " + getName()
                + "\nType: " + QString( (0 == parent() ) ? "Main project" : (isLeaf() ? "Task" : "Subproject") )
                + "\nDelivery: " + deadlineDelivery().toString()
                + "\nDeadline for copywriters: " + deadlineCopywriters().toString();

        return strData;
    }

    case KotkaSource::DeliveryDateRole:
    {
        return deadlineDelivery();
    }

    case KotkaSource::WritersDeadlineDateRole:
    {
        return deadlineCopywriters();
    }

    case KotkaSource::ObjectNameRole:
    {
        return getName();
    }

    case KotkaSource::ObjectTypeRole:
    {
        return QString( (0 == parent() ) ? "Main project" : (isLeaf() ? "Task" : "Subproject") );
    }

    default:
        return QStandardItem::data(a_iRole);
    }
}

void IProject::setData(const QVariant &a_value, int a_iRole)
{
    switch(a_iRole)
    {
    case KotkaSource::ProjectDescDispRole:
    {
        break;
    }

    case KotkaSource::DeliveryDateRole:
    {
        setDeadlineDelivery(a_value.toDateTime() );
        break;
    }

    case KotkaSource::WritersDeadlineDateRole:
    {
        setDeadlineCopywriters(a_value.toDateTime() );
        break;
    }

    case KotkaSource::ObjectNameRole:
    {
        setName(a_value.toString() );
        break;
    }

    case KotkaSource::ObjectTypeRole:
    {
        break;
    }

    default:
        QStandardItem::setData(a_value, a_iRole);
    }
}

void IProject::fillInSourcesModel(const QList<KotkaSource::SSourceData> &a_rSourceList)
{
    Q_UNUSED(a_rSourceList)
}
