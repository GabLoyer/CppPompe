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

static void TomatoController::StartArroser()
{
    TomatoController::bEstEnTrainDArroser = true;
    Serial.println("Les plantes ont soif, on arrose");
    digitalWrite(PIN_POMPE, HIGH);

    pStopTimer.enable(TomatoController::pStopTimerId);
}

static void TomatoController::StopArroser()
{
    TomatoController::bEstEnTrainDArroser = false;
    Serial.println("Désactivation de la pompe ...");
    digitalWrite(PIN_POMPE, LOW);

    pStopTimer.disable(TomatoController::pStopTimerId);
}