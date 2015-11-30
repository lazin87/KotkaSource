#include "mainwindow.h"
#include <QApplication>


// headers to test
#include "cprojectmanager.h"
#include "cclientsandwritersdbmodel.h"
#include "xlsxdocument.h"
#include <QDebug>
// end headers to test
QString GetRandomString();

void fillInAddressBook(CClientsAndWritersDbModel & a_rAddressBook);
void testXlsxParser()
{
    qDebug() << "CXlsxCastoSourceParser::getTaskDataList";
    QXlsx::Document oDoc("C:/Users/Rafal/Downloads/test.xlsx");

    QString strCell = "A1";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "D8";
    qDebug() << strCell << " " << oDoc.read(strCell);

    strCell = "B5";
    qDebug() << strCell << " " << oDoc.read(strCell);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // just to test
    CProjectManager oProjectMngr;
    w.setModel(oProjectMngr.getModel() );

    QObject::connect( &w, SIGNAL(createProject(KotkaSource::SProjectData&,QModelIndex&, QList<KotkaSource::SSourceData> &) )
                    , &oProjectMngr, SLOT(createProjectSlot(KotkaSource::SProjectData&, QModelIndex&, QList<KotkaSource::SSourceData> &) )
                    );
    QObject::connect( &w, SIGNAL(createTask(KotkaSource::STaskData&,QModelIndex&) )
                    , &oProjectMngr, SLOT(createTaskSlot(KotkaSource::STaskData&,QModelIndex&) )
                    );

    CClientsAndWritersDbModel oAddressBook;
  //  fillInAddressBook(oAddressBook);
    w.setModelForAddressBook(&oAddressBook);
    QObject::connect( &w, SIGNAL(addNewContact(KotkaSource::SContactData const &) )
                    , &oAddressBook, SLOT(addNewContactSlot(KotkaSource::SContactData const &) )
                    );

    // end just to test


    return a.exec();
}

void fillInAddressBook(CClientsAndWritersDbModel & a_rAddressBook)
{
    const int iCONTACTS_NBR = 40;

    for(int i = 0; iCONTACTS_NBR > i; ++i)
    {
        a_rAddressBook.append(GetRandomString() );
    }
}

QString GetRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
