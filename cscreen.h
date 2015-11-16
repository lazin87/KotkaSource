#ifndef CSCREEN_H
#define CSCREEN_H

#include "QObject"

class QTextBrowser;

class CScreen : public QObject
{
    Q_OBJECT
public:
    struct SProjectData
    {
        QString m_strName;
    };

    CScreen(QTextBrowser * a_pTextBrowser, QObject * a_pParent = 0);
    ~CScreen();

public slots:
    void showProject(SProjectData a_oProjectData);

private:
    QTextBrowser * m_pTextBrowser;
};

#endif // CSCREEN_H
