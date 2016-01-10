#ifndef COMMONTEMPLATES_H
#define COMMONTEMPLATES_H

#include <QString>
#include <QDateTime>

template<class T>
struct item_return{ typedef T type; };
template<class T>
typename item_return<T>::type noChange();

template<>
struct item_return<QString>{ typedef QString type; };
template<>
QString noChange<QString>();

template<>
struct item_return<int> {typedef int type; };
template<>
int noChange<int>();

template<>
struct item_return<QDateTime> {typedef QDateTime type; };
template<>
QDateTime noChange<QDateTime>();

#endif // COMMONTEMPLATES_H

