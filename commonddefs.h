#ifndef COMMONDDEFS
#define COMMONDDEFS

#include <qnamespace.h>

#include <QString>
#include <QDateTime>
#include <QMap>
#include <QDir>

#include "cpersonpropertis.h"
#include "csourcepropertis.h"

class CPerson;

namespace KotkaSource {

const int ADDRESS_LENGTH = 200;

const QString strMAIN_APP_PATH = QDir::homePath() + "/KotkaMngr";
const QString strINPUT_FILES_PATH = strMAIN_APP_PATH + "/InputFiles";
const QString strOUTPUT_FILES_PATH = strMAIN_APP_PATH + "/OutputFiles";

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

enum ETaskObjectType
{
    eTOT_Text,
    eTOT_File
};

struct SProjectData
{
    QString m_strName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;
    QString m_strClientName;
    CPerson * m_pClient;
};

struct STaskObjectData
{
    int m_iMinLength;
    int m_iMaxLength;
    ETaskObjectType m_eType;
    QString m_strCurrentText;
};

struct STaskData
{
    QString m_strName;
    QString m_strWriterName;
    QDateTime m_oDateTimeDelivery;
    QDateTime m_oDateTimeWriterDeadline;

    QMap<QString, STaskObjectData> m_aTextFieldsMap;
};

struct SContactData
{
    QString m_strEmail;
    QString m_strName;
    QString m_strPhone;
    QString m_strAddress;

    bool m_fIsWriter;
    bool m_fIsClient;
};

struct SSourceData
{
    QString m_strName;
    QString m_strParserName;
    bool m_fReadOnly;
};

}

Q_DECLARE_METATYPE(KotkaSource::SProjectData)
Q_DECLARE_METATYPE(KotkaSource::SContactData)
Q_DECLARE_METATYPE(KotkaSource::SSourceData)

#endif // COMMONDDEFS

