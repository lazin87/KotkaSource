#include "isource.h"

#include <QDebug>

#include "isourceparsestrategy.h"

ISource::ISource(QString const & a_rFileName)
    : m_pParseStrategy(0)
    , m_fIsReadOnly(true)
    , m_oFile(a_rFileName)
    , m_strName(a_rFileName)
{

}

ISource::~ISource()
{
    qDebug() << "ISource::~ISource()";
}

void ISource::setStrategy(ISourceParseStrategy *a_pParseStrategy)
{
    m_pParseStrategy = a_pParseStrategy;
}

ISourceParseStrategy *ISource::strategy() const
{
    return m_pParseStrategy;
}

void ISource::setReadOnlyFlag(bool a_fIsReadOnly)
{
    m_fIsReadOnly = a_fIsReadOnly;
}

bool ISource::readTaskData(QList<KotkaSource::STaskData> a_rOutTaskList)
{
    bool fResult = false;

    if( (0 != m_pParseStrategy) && m_oFile.exists() )
    {
        fResult = m_oFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(fResult)
        {
            QTextStream inTextStream(&m_oFile);
            fResult = m_pParseStrategy->getTaskDataList(a_rOutTaskList, inTextStream);
            m_oFile.close();
        }
    }

    return fResult;
}

bool ISource::storeTaskData(const KotkaSource::STaskData &a_crTaskData)
{
    bool fResult = false;

    if( (false == m_fIsReadOnly) && (0 != m_pParseStrategy) && m_oFile.exists() )
    {
        fResult = m_oFile.open(QIODevice::ReadWrite | QIODevice::Text);
        if(fResult)
        {
            QTextStream inOutTextStream(&m_oFile);
            fResult = m_pParseStrategy->fillInSourceDoc(a_crTaskData, inOutTextStream);
            inOutTextStream.flush();
            m_oFile.close();
        }
    }

    return fResult;
}

QString ISource::getName() const
{
    return m_strName;
}

