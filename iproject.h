#ifndef CPROJECT_H
#define CPROJECT_H

#include <QString>
#include <QDateTime>
#include <QStandardItem>

class IProject : public QStandardItem
{
public:
    explicit IProject(QString a_strName, const IProject * a_pProjectParent = 0);
    virtual ~IProject();

    virtual bool isLeaf() const;

    QString strName() const;
    void setStrName(const QString &a_rstrName);

    QDateTime deadlineDelivery() const;
    void setDeadlineDelivery(const QDateTime &a_rDeadlineDelivery);

    QDateTime deadlineCopywriters() const;
    void setDeadlineCopywriters(const QDateTime &a_rDeadlineCopywriters);

    virtual bool addChild(IProject * a_pChild) = 0;
    virtual IProject * peekChild(int a_iIndex) = 0;
    virtual bool removeChild(int a_iIndex) = 0;
    virtual void removeAllChildren() = 0;

    virtual QStandardItem  * getStandardItem() = 0;

protected:
    const IProject * m_pProjectParent;

    QString m_strName;

    QDateTime m_oDeadlineDelivery;
    QDateTime m_oDeadlineCopywriters;



    // TO DO dodac membera do przechowywania zrodel
};

#endif // CPROJECT_H
