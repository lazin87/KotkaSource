#ifndef COMMONDDEFS
#define COMMONDDEFS

#include <qnamespace.h>

#include <QString>
#include <QDateTime>

namespace KotkaSource {
enum
{
    ProjectDescDispRole = Qt::UserRole + 1,
    DeliveryDateRole,
    WritersDeadlineDateRole,
    ObjectNameRole,
    ObjectTypeRole
};

struct SProjectData
{
    QString m_strName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;
};

}
#endif // COMMONDDEFS

