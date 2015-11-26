#include "isource.h"

#include "isourcetranslatestrategy.h"

ISource::ISource()
    : m_pTranslateStrategy(0)
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

