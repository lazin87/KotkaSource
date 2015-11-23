#include "cpersonpropertis.h"

const QString CPersonPropertis::s_aPropertisLabels[] = {
      "Name"
    , "Email"
    , "Phone"
    , "Is Writer"
    , "Is Client"
};

int CPersonPropertis::toInt(const CPersonPropertis::EPersonPropertis &a_crProperty)
{
    return static_cast<int>(a_crProperty);
}

CPersonPropertis::EPersonPropertis CPersonPropertis::mapToPersonProperty(int a_iIndex)
{
    EPersonPropertis eResultPropertis = eInvalid;
    if( (eFirst <= a_iIndex) && (eNumberOfPropertis > a_iIndex) )
    {
        eResultPropertis = static_cast<EPersonPropertis>(a_iIndex);
    }

    return eResultPropertis;
}

int CPersonPropertis::count()
{
    return static_cast<int>(eNumberOfPropertis);
}

CPersonPropertis::CPersonPropertis()
{

}

