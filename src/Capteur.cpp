

#include "Capteur.h"

Capteur::Capteur(short p_nPinNumber)
    :nPinNumber(p_nPinNumber)
{
}

Capteur::Capteur(short p_nPinNumber, float p_fResistanceValue)
    :nPinNumber(p_nPinNumber),
    fResistanceValue(p_fResistanceValue)
{
}

float Capteur::GetValue()
{
    return fValue;
}