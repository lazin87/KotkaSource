#include "iproject.h"

#include <QDebug>

IProject::IProject(QString a_strName, const IProject *a_pProjectParent)
    : QStandardItem(a_strName)
    //, m_pProjectParent(a_pProjectParent)
    , m_strName(a_strName)
    , m_oDeadlineDelivery()
    , m_oDeadlineCopywriters()
{

}

IProject::~IProject()
{

}

bool IProject::isLeaf() const
{
    return false;
}

//QString IProject::strName() const
//{
//    return m_strName;
//}

//void IProject::setStrName(const QString &a_rstrName)
//{
//    m_strName = a_rstrName;
//    QStandardItem::setText(m_strName);
//}

QDateTime IProject::deadlineDelivery() const
{
    QDateTime oOutDateTime = m_oDeadlineDelivery;

    if(false == oOutDateTime.isValid() )
    {
        QStandardItem * pParentItem = parent();

        if( 0 != pParentItem )
        {
            oOutDateTime = pParentItem->data(KotkaSource::DeliveryDateRole).toDateTime();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

//void IProject::setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery)
//{
//    m_oDeadlineDelivery = a_rDeadlineDelivery;
//}

QDateTime IProject::deadlineCopywriters() const
{
    QDateTime oOutDateTime = m_oDeadlineCopywriters;

    if(false == oOutDateTime.isValid() )
    {
        QStandardItem * pParentItem = parent();

        if( 0 != pParentItem )
        {
            oOutDateTime = pParentItem->data(KotkaSource::DeadlineDateRole).toDateTime();

            if(false == oOutDateTime.isValid() )
            {
                qWarning("CProject::deadlineDelivery(): invalid");
            }
        }
    }

    return oOutDateTime;
}

//void IProject::setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters)
//{
//    m_oDeadlineCopywriters = a_rDeadlineCopywriters;
//}

QVariant IProject::data(int a_iRole) const
{
    switch(a_iRole)
    {

    case KotkaSource::ProjectDescDispRole:
    {
        QString strData = "Name: " + m_strName
                + "\nType: " + QString( (0 == parent() ) ? "Main project" : (isLeaf() ? "Task" : "Subproject") )
                + "\nDelivery: " + deadlineDelivery().toString()
                + "\nDeadline for copywriters: " + deadlineCopywriters().toString();

        return strData;
    }

    case KotkaSource::DeliveryDateRole:
    {
        return deadlineDelivery();
    }

    case KotkaSource::DeadlineDateRole:
    {
        return deadlineCopywriters();
    }

    case KotkaSource::ObjectNameRole:
    {
        return m_strName;
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
        m_oDeadlineDelivery = a_value.toDateTime();
        break;
    }

    case KotkaSource::DeadlineDateRole:
    {
        m_oDeadlineCopywriters = a_value.toDateTime();
        break;
    }

    case KotkaSource::ObjectNameRole:
    {
        m_strName = a_value.toString();
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
