#include "csourcesmodel.h"

#include <QDir>
#include <QFileInfo>
#include <QDebug>


CSourcesModel::CSourcesModel(const QString &a_strModelName, QObject *a_pParent)
    : QAbstractTableModel(a_pParent)
    , m_strName( (a_strModelName.isEmpty() ) ? "Undefined" : a_strModelName)
    , m_oXlsxCastoParser()
{
    prepareInOutFolders();
}

CSourcesModel::~CSourcesModel()
{
    clearSourcesList();
}



int CSourcesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_aPtrsSourcesList.count();
}

int CSourcesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return CSourcePropertis::count();
}

QVariant CSourcesModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {

    }

    case Qt::CheckStateRole:
    {

    }
    default:
        return QVariant();
    }
}

void CSourcesModel::getTaskListFromSources(QList<T_SourceTaskDataPair> &a_rListOfTaskDataPairs)
{
    qDebug() << "CSourcesModel::getTaskListFromSources";
    foreach(ISource * pSource, m_aPtrsSourcesList)
    {
        qDebug() << "CSourcesModel::getTaskListFromSources: loop";
        if(0 != pSource)
        {
            qDebug() << "CSourcesModel::getTaskListFromSources: if";
            QList<KotkaSource::STaskData> taskDataList;
            bool fTaskListWereCollected = pSource->readTaskData(taskDataList);

            if(fTaskListWereCollected)
            {
                T_SourceTaskDataPair sourceAndTasksPair{pSource->getName(), taskDataList};
                a_rListOfTaskDataPairs.append(sourceAndTasksPair);
            }
        }
    }
}

void CSourcesModel::addNewSource(const QString &a_strName, bool a_fReadOnly, QString a_strParserName)
{
    QFileInfo oFileInfo(a_strName);
    QString fileName = oFileInfo.fileName();
    makeFileNameUnique(fileName);

    // copy file to input data
    QFile::copy( a_strName
               , KotkaSource::strINPUT_FILES_PATH + "/" + m_strName +"/" + fileName
               );

    // copy file to output data
    if(!a_fReadOnly)
    {
        QFile::copy( a_strName
                   , KotkaSource::strOUTPUT_FILES_PATH + "/" + m_strName +"/" + fileName
                   );
    }

    ISource * iSource = new ISource(fileName);
    iSource->setParentModelName(m_strName);
    if(false == a_strParserName.isEmpty() )
    {
        qDebug() << "CSourcesModel::addNewSource: Parser was set for: " << a_strName;
        iSource->setStrategy( &m_oXlsxCastoParser);
    }

    beginInsertRows(QModelIndex(), rowCount(QModelIndex() ), rowCount(QModelIndex() ) );
    m_aPtrsSourcesList.append(iSource);
    endInsertRows();
}

void CSourcesModel::removeSourceSlot(const QModelIndex &a_rModelIndex)
{
    QString strFileName = m_aPtrsSourcesList[a_rModelIndex.row() ]->getName();
    QFile::remove(KotkaSource::strINPUT_FILES_PATH + "/" + m_strName +"/" + strFileName);
    QFile::remove(KotkaSource::strOUTPUT_FILES_PATH + "/" + m_strName +"/" + strFileName);

    // sprawdzic czy wywolac destruktor!!

    beginRemoveRows(QModelIndex(), a_rModelIndex.row(), a_rModelIndex.row() );
    m_aPtrsSourcesList.removeAt(a_rModelIndex.row() );
    endRemoveRows();

}

void CSourcesModel::clearSourcesList()
{
    foreach(ISource * pSoruce, m_aPtrsSourcesList)
    {
        if(0 != pSoruce)
        {
            delete pSoruce;
            pSoruce = 0;
        }
    }
}

void CSourcesModel::prepareInOutFolders()
{
    QDir oDirMngr;
    oDirMngr.mkdir(KotkaSource::strINPUT_FILES_PATH + "/" + m_strName);
    oDirMngr.mkdir(KotkaSource::strOUTPUT_FILES_PATH + "/" + m_strName);
}

void CSourcesModel::makeFileNameUnique(QString &a_rFileName)
{
    QFileInfo oFileInfo;
    bool fExist;

    oFileInfo.setFile(KotkaSource::strINPUT_FILES_PATH + "/" + m_strName + "/" + a_rFileName);
    fExist = oFileInfo.exists();

    oFileInfo.setFile(KotkaSource::strOUTPUT_FILES_PATH + "/" + m_strName + "/" + a_rFileName);
    fExist |= oFileInfo.exists();

    if(fExist)
    {
        QString newName;
        const int iMAX_SAME_FILE_NAMES = 1000;
        oFileInfo.setFile(a_rFileName);

        for(int i = 0; (iMAX_SAME_FILE_NAMES > i) && fExist; ++i)
        {
            newName = oFileInfo.baseName() + "-" + i + "." + oFileInfo.completeSuffix();

            oFileInfo.setFile(KotkaSource::strINPUT_FILES_PATH + "/" + m_strName + "/" + newName);
            fExist = oFileInfo.exists();

            oFileInfo.setFile(KotkaSource::strOUTPUT_FILES_PATH + "/" + m_strName + "/" + newName);
            fExist |= oFileInfo.exists();
        }

        a_rFileName = newName;
    }
}
