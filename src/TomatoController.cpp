#include "TomatoController.h"
#include "General.h"

TomatoController::TomatoController()
{
    bEstEnTrainDArroser = false;
    pinMode(PIN_POMPE, OUTPUT);
    pinMode(PIN_DEL, OUTPUT);

    pStopTimerId = pStopTimer.setInterval(DUREE_ARROSAGE * NB_MS_IN_SECOND, StopArroser);
    pStopTimer.disable(pStopTimerId);
}

TomatoController::~TomatoController()    
{
    if (bEstEnTrainDArroser)
    {
        StopArroser();
    }
}

void TomatoController::loop()
{
    if (bEstEnTrainDArroser)
    {
        pStopTimer.run();
    }
}
