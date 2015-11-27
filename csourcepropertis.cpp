#include "csourcepropertis.h"

const QString CSourcePropertis::s_aPropertisLabels[] = {
      "Name"
    , "Read Only"
    , "Parser"
};

int CSourcePropertis::toInt(const ESourcePropertis &a_crProperty)
{
    return static_cast<int>(a_crProperty);
}

CSourcePropertis::ESourcePropertis CSourcePropertis::mapToPersonProperty(int a_iIndex)
{
    ESourcePropertis eResultPropertis = eInvalid;
    if( (eFirst <= a_iIndex) && (eNumberOfPropertis > a_iIndex) )
    {
        eResultPropertis = static_cast<ESourcePropertis>(a_iIndex);
    }

    return eResultPropertis;
}

int CSourcePropertis::count()
{
    return static_cast<int>(eNumberOfPropertis);
}

CSourcePropertis::CSourcePropertis()
{

}
