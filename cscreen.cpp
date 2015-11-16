#include "cscreen.h"

#include <QDebug>
#include <QTextBrowser>

CScreen::CScreen(QTextBrowser a_pTextBrowser, QObject a_pParent)
    : QObject(a_pParent)
    , m_pTextBrowser(a_pTextBrowser)
{

}

CScreen::~CScreen()
{

}

void CScreen::showProject(CScreen::SProjectData a_oProjectData)
{
    if(0 != m_pTextBrowser)
    {
        QString strTextToDisplay = "";
        strTextToDisplay << a_oProjectData.m_strName;

        m_pTextBrowser->setPlainText(strTextToDisplay);
    }
    else
    {
        qDebug() << "CScreen::showProject(): NULL PTR";
    }
}

