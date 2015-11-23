#ifndef CPERSONPROPERTIS_H
#define CPERSONPROPERTIS_H

#include <QString>

class CPersonPropertis
{
public:
    enum EPersonPropertis
    {
        eInvalid = -1,
        eFirst = 0,
        eName = 0,
        eEmail,
        ePhone,
        eIsWriter,
        eIsClient,

        eNumberOfPropertis
    };

public:
    static int toInt(EPersonPropertis const & a_crProperty);
    static EPersonPropertis mapToPersonProperty(int a_iIndex);
    static int count();
    static const QString s_aPropertisLabels[eNumberOfPropertis];

private:
    CPersonPropertis();
};

#endif // CPERSONPROPERTIS_H
