#ifndef ISOURCE_H
#define ISOURCE_H

class ISourceTranslateStrategy;

class ISource
{
public:
    ISource();

    void setStrategy(ISourceTranslateStrategy * a_pTranslateStrategy);
    ISourceTranslateStrategy * strategy() const;

private:
    ISourceTranslateStrategy * m_pTranslateStrategy;
};

#endif // ISOURCE_H
