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
    ObjectEmailRole,
    ObjectPhoneRole,
    ObjectAddressRole,
    ObjectTypeRole,
    ReadProjectDataRole,
    SetProjectDataRole
};

enum ETaskState
{
    eTS_Invalid = 0,
    eTS_Unassigned,
    eTS_Assigned,
    eTS_Wrote,
    eTS_Reviewed,
    eTS_Sent,
    eTS_ToCorrect,
    eTS_Completed
};

enum EObjectType
{
    eOT_MainProject,
    eOT_SubProjectm,
    eOT_Task
};

struct SProjectData
{
    QString m_strName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;
};

struct STaskData
{
    QString m_strName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;
};

}

Q_DECLARE_METATYPE(KotkaSource::SProjectData)

#endif // COMMONDDEFS

