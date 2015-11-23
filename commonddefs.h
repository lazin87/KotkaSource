#ifndef COMMONDDEFS
#define COMMONDDEFS

#include <qnamespace.h>

#include <QString>
#include <QDateTime>

class CPerson;

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
    SetProjectDataRole,
    ContactIsWriterRole,
    ContactIsClientRole,
    ReadContactDataRole,
    SetContactDataRole
};

enum EPersonPropertis
{
    ePP_Invalid = -1,
    ePP_First = 0,
    ePP_Name = 0,
    ePP_Email,
    ePP_Phone,
    ePP_isWriter,
    ePP_isClient,

    ePP_NumberOfPropertis
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
    QString m_strClientName;
    CPerson * m_pClient;
};

struct STaskData
{
    QString m_strName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;
};

struct SContactData
{
    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;

    bool m_fIsWriter;
    bool m_fIsClient;
};

}

Q_DECLARE_METATYPE(KotkaSource::SProjectData)
Q_DECLARE_METATYPE(KotkaSource::SContactData)

#endif // COMMONDDEFS

