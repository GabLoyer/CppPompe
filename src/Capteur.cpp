

#include "Capteur.h"
#include "General.h"

Capteur::Capteur(short p_nPinNumber, bool p_bIsOut)
{
    nPinNumber = p_nPinNumber;
    pinMode(nPinNumber, p_bIsOut ? OUTPUT : INPUT);
}

Capteur::Capteur(short p_nPinNumber, float p_fResistanceValue, bool p_bIsOut)    
{
    nPinNumber = p_nPinNumber;
    fResistanceValue = p_fResistanceValue;
}

float Capteur::GetValue()
{
    return fValue;
}