#include "isource.h"

#include "isourcetranslatestrategy.h"

ISource::ISource(QString const & a_rFileName)
    : m_pTranslateStrategy(0)
    , m_fIsReadOnly(true)
    , m_oFile(a_rFileName)
{

}

void ISource::setStrategy(ISourceTranslateStrategy *a_pTranslateStrategy)
{
    m_pTranslateStrategy = a_pTranslateStrategy;
}

ISourceTranslateStrategy *ISource::strategy() const
{
    return m_pTranslateStrategy;
}

void ISource::setReadOnlyFlag(bool a_fIsReadOnly)
{
    m_fIsReadOnly = a_fIsReadOnly;
}

bool ISource::readTaskData(QList<KotkaSource::STaskData> a_rOutTaskList)
{
    bool fResult = false;

    if( (0 != m_pTranslateStrategy) && m_oFile.exists() )
    {
        fResult = m_oFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(fResult)
        {
            QTextStream inTextStream(&m_oFile);
            fResult = m_pTranslateStrategy->getTaskDataList(a_rOutTaskList, inTextStream);
            m_oFile.close();
        }
    }

    return fResult;
}

bool ISource::storeTaskData(const KotkaSource::STaskData &a_crTaskData)
{
    bool fResult = false;

    if( (false == m_fIsReadOnly) && (0 != m_pTranslateStrategy) && m_oFile.exists() )
    {
        fResult = m_oFile.open(QIODevice::ReadWrite | QIODevice::Text);
        if(fResult)
        {
            QTextStream inOutTextStream(&m_oFile);
            fResult = m_pTranslateStrategy->fillInSourceDoc(a_crTaskData, inOutTextStream);
            inOutTextStream.flush();
            m_oFile.close();
        }
    }

    return fResult;
}

