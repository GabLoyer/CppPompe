// Gère la modification de valeur runtime

#include "ValueChanger.h"
#include "main.cpp"


     /*enum eVariable {
        eDUREE_MIN,
        eDUREE_MAX,
        eINTERVAL_MIN,
        eINTERVAL_MAX,
        eSOLEIL_NUIT,
        eUNKNOWN
    };*/

ValueChanger::ValueChanger() {
    pinMode(PIN_SUBSTRACT, INPUT);
    pinMode(PIN_ADD, INPUT);
    pinMode(PIN_DUREE_MIN, INPUT);
    pinMode(PIN_DUREE_MAX, INPUT);
    pinMode(PIN_INTERVAL_MIN, INPUT);
    pinMode(PIN_INTERVAL_MAX, INPUT);
    pinMode(PIN_VAL_SOLEIL_NUIT, INPUT);

    mCurrentVariable = eUNKNOWN;
};

ValueChanger::~ValueChanger() {
};

eVariable ValueChanger::getCurrentVariable()
{
    return mCurrentVariable;
}

void ValueChanger::setCurrentVariable(eVariable variable)
{
    mCurrentVariable = variable;
}

void ValueChanger::updateLoop()
{
    int delta = 0;
    int val_minus = digitalRead(PIN_SUBSTRACT);
    int val_add = digitalRead(PIN_ADD);

    if (val_minus == HIGH)
        delta -= 1;

    if (val_add == HIGH)
        delta += 1;

    // Update value
    modifyValueofVariable(delta);

    // Update display
    
}

void ValueChanger::modifyValueofVariable(int delta)
{
    switch (mCurrentVariable)
    {
        case eDUREE_MIN:
            dureeMin += delta;
            dureeMin = constrain(dureeMin, DUREE_MIN, DUREE_MAX);
        case eDUREE_MAX:
            dureeMax += delta;
            dureeMax = constrain(dureeMax, DUREE_MIN, DUREE_MAX);
            break;
        case eINTERVAL_MIN:
            intervalMin += delta;
            intervalMin = constrain(intervalMin, INTERVAL_MIN, INTERVAL_MAX);
        case eINTERVAL_MAX:
            intervalMax += delta;
            intervalMax = constrain(intervalMax, INTERVAL_MIN, INTERVAL_MAX);
            break;
        case eSOLEIL_NUIT:
            valSoleilNuit += delta;
            valSoleilNuit = constrain(valSoleilNuit, 0, SOLEIL_MAX);
            break;
        case eUNKNOWN:
        default:
            break;
    }
}
