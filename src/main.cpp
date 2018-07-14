
#include "General.h"

#include "TomatoController.h"
#include "ScreenManager.h"

#include <dht11.h>

ScreenManager* pScreenManager;
//TomatoController pTomatoController = TomatoController();

// the timer object
dht11 DHT11;
#define DHT11PIN 35

SimpleTimer pTimerArrosage;
ValueChanger pValueChanger;

int nStopTimerId;
int nStartTimerId;

unsigned long Duree = DUREE_ARROSAGE;
unsigned long Interval = INTERVAL_ARROSAGE;

char tempChar[4];
char tempChar2[4];
char tempChar3[4];
char tempChar4[4];
bool bEstEnTrainDArroser = false;
int nbArrosage = 0;
bool bNuit = false;

long intervalMin 20     // En minutes, l'interval de temp qu'on arrose quand le soleil est max.
long intervalMax 60     // En minutes, l'interval de temp qu'on arrose quand le soleil est min.
long dureeMin 90        // En secondes, on arrose ce temps quand la temperature est min.
long dureeMax 150       // En secondes, on arroce ce temps quand la temperature est max.
long valSoleilNuit 60   // Correspond a la valeur minimum de soleil avant l'arrosage.

void RecalculerIntervalEtDuree();

void StartArroser()
{
    bEstEnTrainDArroser = true;
    ++nbArrosage;
    Serial.println("Les plantes ont soif, on arrose");
    digitalWrite(PIN_POMPE, HIGH);

    pTimerArrosage.enable(nStopTimerId);
    pTimerArrosage.disable(nStartTimerId);
}


void StopArroser()
{
    bEstEnTrainDArroser = false;
    Serial.println("Désactivation de la pompe ...");
    digitalWrite(PIN_POMPE, LOW);

    // Recalculer l'interval et durée.
    RecalculerIntervalEtDuree();
}

void lireCapteurTemperature()
{
    int chk = DHT11.read(DHT11PIN);
    switch (chk)
    {
    case DHTLIB_OK:  
        Serial.print("OK,\t"); 
        break;
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.print("Checksum error,\t"); 
        break;
    case DHTLIB_ERROR_TIMEOUT: 
        Serial.print("Time out error,\t"); 
        break;
    default: 
        Serial.print("Unknown error,\t"); 
        break;
    }
    // DISPLAY DATA
    Serial.print(DHT11.humidity, 1);
    Serial.print(",\t");
    Serial.println(DHT11.temperature, 1);
    Serial.println(" , \n");
    Serial.println(analogRead(DHT11PIN));
}

int lireCapteurSoleil()
{
    int soleil = map(analogRead(PIN_PHOTO_RESISTANCE), 0, 1023, 0, 100);
    Serial.println("Voici l'indice soleil pour aujord'hui : \n");
    Serial.println(soleil);
    return soleil;
}

void setup() {
    Serial.begin(9600);

    Serial.println("Screen Begin");

    bEstEnTrainDArroser = false;
    pinMode(PIN_POMPE, OUTPUT);
    pinMode(PIN_DEL, OUTPUT);
    pinMode(PIN_CAPTEUR, INPUT);
    pinMode(PIN_POMPE_GROUND, OUTPUT);
    digitalWrite(PIN_POMPE_GROUND, LOW);

    nStopTimerId = pTimerArrosage.setInterval(Duree * NB_MS_IN_SECOND, StopArroser);
    pTimerArrosage.disable(nStopTimerId);
    nStartTimerId = pTimerArrosage.setInterval(Interval * NB_MS_IN_MINUTE, StartArroser);

    Serial.println("Setup the screen");
    pScreenManager = new ScreenManager();

    Serial.println("Finish setup, starting to loop..");

    String temp = String(DHT11.temperature);
    temp.toCharArray(tempChar, 4);
    pScreenManager->SetLine(0, "Temp : ", tempChar);
    
    temp = String(DHT11.humidity);
    
    temp.toCharArray(tempChar2, 4);
    pScreenManager->SetLine(1, "Humidity : ", tempChar2);

    temp = String(0);
    temp.toCharArray(tempChar3, 18);
    pScreenManager->SetLine(2, "Soleil : ", tempChar3);

    temp = String(nbArrosage);
    temp.toCharArray(tempChar4, 18);
    pScreenManager->SetLine(3, "Nb Arros. : ", tempChar4);

    pScreenManager->UpdateDisplay(false);
}


void loop() {
    pTimerArrosage.run();

    // Verifier si on essaye de modifier des valeurs de duree ou d'interval.
    pValueChanger.updateLoop()

    lireCapteurTemperature();

    int indiceSoleil = lireCapteurSoleil();

    if (indiceSoleil < VAL_SOLEIL_NUIT)
    {
        bNuit = true;
        pScreenManager->ClearDisplay(false);
        pScreenManager->SetLine(3, "C'est la nuit", "");
        pTimerArrosage.disable(nStartTimerId);
        pScreenManager->UpdateDisplay(false);
        nbArrosage = 0;
        delay(2000);
    }
    else{
        if(bNuit)
        {
            pScreenManager->ClearDisplay(false);
            String temp = String(nbArrosage);
            temp.toCharArray(tempChar4, 18);
            pScreenManager->SetLine(3, "Nb Arros. : ", tempChar4);
            pTimerArrosage.enable(nStartTimerId); 
            pScreenManager->UpdateDisplay(false); 
            bNuit = false;      
        }
    }

    //pTomatoController.loop();
    pScreenManager->ClearDisplay(true);

    String temp = String(DHT11.temperature);
    temp.toCharArray(tempChar, 4);
    pScreenManager->SetLine(0, tempChar);
    
    temp = String(DHT11.humidity);
    
    temp.toCharArray(tempChar2, 4);
    pScreenManager->SetLine(1, tempChar2);

    temp = String(indiceSoleil);
    temp.toCharArray(tempChar3, 18);
    pScreenManager->SetLine(2, tempChar3);

    if(!bNuit)
    {
        temp = String(nbArrosage);
        temp.toCharArray(tempChar4, 18);
        pScreenManager->SetLine(3, tempChar4);
    }

    pScreenManager->UpdateDisplay(true);

    //On attend une seconde avant de réappelé le système
    Serial.println("Finish loop, looping back in 2 sec..");
    delay(1000);
}

int GetNextInterval()
{
    int soleil = lireCapteurSoleil();
    int interval = map(soleil, SOLEIL_MIN, SOLEIL_MAX, intervalMax, intervalMin);
    interval = constrain(interval, intervalMin, intervalMax);
    return interval;
}

int GetNextDuree()
{
    int temperature = DHT11.temperature;
    int duree = map(temperature, TEMPERATURE_MIN, TEMPERATURE_MAX, dureeMin, dureeMax);
    duree = constrain(duree, dureeMin, dureeMax);
    return duree;
}

void RecalculerIntervalEtDuree()
{
    Interval = GetNextInterval();
    Duree = GetNextDuree();

    pTimerArrosage.deleteTimer(nStartTimerId);
    pTimerArrosage.deleteTimer(nStopTimerId);

    nStopTimerId = pTimerArrosage.setInterval(Duree * NB_MS_IN_SECOND, StopArroser);
    pTimerArrosage.disable(nStopTimerId);
    nStartTimerId = pTimerArrosage.setInterval(Interval * NB_MS_IN_MINUTE, StartArroser);

    pTimerArrosage.disable(nStopTimerId);
    pTimerArrosage.enable(nStartTimerId);
}
