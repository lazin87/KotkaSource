#ifndef CSOURCEPROPERTIS_H
#define CSOURCEPROPERTIS_H

#include <QString>

class CSourcePropertis
{
public:
    enum ESourcePropertis
    {
        eInvalid = -1,
        eFirst = 0,
        eName = 0,
        eIsReadOnly,
        eParser,

        eNumberOfPropertis
    };

public:
    static int toInt(const ESourcePropertis &a_crProperty);
    static ESourcePropertis mapToPersonProperty(int a_iIndex);
    static int count();
    static const QString s_aPropertisLabels[eNumberOfPropertis];

private:
    CSourcePropertis();
};

#endif // CSOURCEPROPERTIS_H
