#include "commontemplates.h"

template<class T>
typename item_return<T>::type noChange(){ return T(); }

template<>
QString noChange<QString>(){ return "##"; }

template<>
int noChange<int>(){ return -12; }

template<>
QDateTime noChange<QDateTime>(){ return QDateTime(); }
