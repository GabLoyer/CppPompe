
#include "General.h"

#include "TomatoController.h"
#include "ScreenManager.h"

//ScreenManager pScreenManager = ScreenManager();
//TomatoController pTomatoController = TomatoController();

// the timer object
SimpleTimer pTimerArrosage;

int nStopTimerId;
int nStartTimerId;

unsigned long Duree = DUREE_ARROSAGE;
unsigned long Interval = INTERVAL_ARROSAGE;

bool bEstEnTrainDArroser = false;


void StartArroser()
{
    bEstEnTrainDArroser = true;
    Serial.println("Les plantes ont soif, on arrose");
    digitalWrite(PIN_POMPE, HIGH);
    digitalWrite(PIN_LED, HIGH);

    pTimerArrosage.enable(nStopTimerId);
    pTimerArrosage.disable(nStartTimerId);
}


void StopArroser()
{
    bEstEnTrainDArroser = false;
    Serial.println("Désactivation de la pompe ...");
    digitalWrite(PIN_POMPE, LOW);
    digitalWrite(PIN_LED, LOW);

    pTimerArrosage.disable(nStopTimerId);
    pTimerArrosage.enable(nStartTimerId);
}


void setup() {
    Serial.begin(9600);

    bEstEnTrainDArroser = false;
    pinMode(PIN_POMPE, OUTPUT);
    pinMode(PIN_DEL, OUTPUT);

    nStopTimerId = pTimerArrosage.setInterval(Duree * NB_MS_IN_SECOND, StopArroser);
    pTimerArrosage.disable(nStopTimerId);
    nStartTimerId = pTimerArrosage.setInterval(Interval * NB_MS_IN_MINUTE, StartArroser);

    Serial.println("Finish setup, starting to loop..");
}


void loop() {
    //pScreenManager.ClearDisplay();

    pTimerArrosage.run();

    //pTomatoController.loop();

    //pScreenManager.UpdateDisplay();

    //On attend une seconde avant de réappelé le système
    Serial.println("Finish loop, looping back in 1 sec..");
    delay(1000);
}