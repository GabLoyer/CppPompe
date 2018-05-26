#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

//Define pour les # de Pin
#define PIN_POMPE 6                        //Le numéro de la Pin où la Pompe est connecté
#define PIN_SOLEIL A0 
#define PIN_ENGRAIS 5
#define PIN_TEMPERATURE A1
#define PIN_EAU_BAS 3
#define PIN_DEL 2

#define cs   10 // Arduino-Pin an Display CS   
#define dc   9  // Arduino-Pin an 
#define rst  8  // Arduino Reset-Pin

//Define pour les mesures des capteurs
#define TEMPERATURE_MIN 18 //TODO : 18 degré Celsius, c'est quoi en V? 
#define TEMPERATURE_MAX 800
#define VAL_SOLEIL_MIN 80
#define SOLEIL_MAX 80
#define SOLEIL_MIN 20


//define pour l'arrossage
#define DUREE_ARROSAGE 30                  //La Durée d'Arrosage en secondes
#define INTERVAL_ARROSAGE 60             //L'intervalle entre chaque arrosage en minutes
#define DEBUT_ARROSAGE 0                     
#define TEMPS_ENGRAIS 5000            //temps de la durée ou la pompe à engrais fonctionne en milliseconde

//Define pour la conversion du temps
#define NB_MILLISECONDES 1000              //Nombre de millisecondes dans une seconde
#define NB_MINUTES 60000                   //Nombre de millisecondes dans une minutes

TFT TFTscreen = TFT(cs, dc, rst);

// char array to print to the screen
char sensorSoleil[4];
char sensorTemp[4];
char tempsArrosage[4];

boolean EtatPompe = LOW;                   //Pompe désactivé au départ
boolean EstEnTrainDArroser = false;
boolean FaitSoleil;
int CptCycleNuit = 0;
int DureeArrosage = DUREE_ARROSAGE;
int IntervalArrosage = INTERVAL_ARROSAGE;
unsigned long MillisecondesEcoulees = INTERVAL_ARROSAGE * NB_MINUTES - 2000;    //variable comptant le temps; on l'initialise pour quel soit à 2000 microsecondes du prochaine arrosage
unsigned long MillisecondesPrecedent = 0;
unsigned long TempsRestant = 0;
unsigned long msEcoules = 0;

unsigned long Duree = 50;
unsigned long Interval = 60;

unsigned long TempsPrec = 0;
unsigned long TempsCourant = 0;
unsigned long TempsPasse = 0;

//Initialisation
void setup()
{
  //Déclaration des entrées/sorties
  pinMode(PIN_POMPE, OUTPUT);              
  pinMode(PIN_ENGRAIS, OUTPUT);
  pinMode(PIN_EAU_BAS, INPUT);
  pinMode(PIN_DEL, OUTPUT);
  
  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  
  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255,255,255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
  TFTscreen.text("Sensor Value :\n ",0,0);
  // ste the font size very large for the loop
  //TFTscreen.setTextSize(3);

  
  Serial.begin(9600);  
}

//Boucle qui sera toujours appelé après le l'initialisation
void loop()
{  
  if(digitalRead(PIN_EAU_BAS))
  {
      //On calcule le temps écoulé
      TempsPrec = TempsCourant;
      TempsCourant = millis();
      TempsPasse = TempsCourant - TempsPrec;
      MillisecondesEcoulees += TempsPasse;
      
      if(!EstEnTrainDArroser)      //le ! signifie une négation, donc si on n'arrose pas
      {     
        VerifierArrosage();
      }
      else
      {
        Arroser();
      }  
      TFTscreen.setTextSize(1);
      TFTscreen.stroke(0,0,0);
      TFTscreen.text("ATTENTION EAU BAS!",0 , 100);
           TFTscreen.setTextSize(2);
  }
  else
  {
         TFTscreen.setTextSize(1);
    TFTscreen.stroke(0,0,255);
      TFTscreen.text("ATTENTION EAU BAS!",0 , 100);
           TFTscreen.setTextSize(2);
  }
  
  AfficherInformations();
    
  //On attend une seconde avant de réappelé le système
  delay(1000);  
  
  EffacerInfos();  
  //TFTscreen.background(0, 0, 0);
}

void EffacerInfos()
{
   TFTscreen.stroke(0,0,0);
   TFTscreen.text("Soleil : ", 0 , 25);
  TFTscreen.text(sensorSoleil, 20, 40);  
      TFTscreen.text("Temperature : ",0,55);
      TFTscreen.text(sensorTemp, 20, 70); 
      TFTscreen.text("Arrosage depuis (sec) :",0 , 120);
      TFTscreen.text(tempsArrosage,0 , 110);
}

void AfficherInformations()
{
  // Read the value of the sensor on A0

  String outputValue = String(CalculerSoleil());
  // convert the reading to a char array
  outputValue.toCharArray(sensorSoleil, 4);

  // set the font color
  TFTscreen.stroke(255,255,255);
  // print the sensor value
   TFTscreen.text("Soleil : ", 0 , 25);
  TFTscreen.text(sensorSoleil, 20, 40);
    
    unsigned long temp = CalculerChaleur();
    
    if(temp > 30)
    {
       TFTscreen.stroke(0,255,255); 
    }
    else
   {
       if (temp > 20)
      {
         TFTscreen.stroke(0,0,255);
      }
       else
      {
         TFTscreen.stroke(128,128,128);
      }
   }


      String charTemp = String(temp);
      charTemp.toCharArray(sensorTemp, 4);
      TFTscreen.text("Temperature : ",0,55);
      TFTscreen.text(sensorTemp, 20, 70);
    
    delay(250);
  
}

void VerifierArrosage()
{
     //On calcule puis on affiche le temps restant au prochain arrosage
     TempsRestant = NB_MINUTES - MillisecondesEcoulees;
     Serial.println("Temps restant avant le prochain arrossage (min): " + TempsRestant / NB_MINUTES);
     
     //on vérifie si on est dû pour le prochain arrosage
     if(VerifierSiTempsEcoule())
     {
           
         if(CalculerSoleil() > SOLEIL_MIN)
         {
             if(CalculerChaleur() > TEMPERATURE_MIN)
             {
               if(CptCycleNuit >= 5)
               {
                   //Premier arrosage de la journée 
                   
                   //TODO
                   //Activer la pompe à engrais
                   digitalWrite(PIN_ENGRAIS,HIGH);
                   delay(TEMPS_ENGRAIS);
                   digitalWrite(PIN_ENGRAIS, LOW);
               }  
                        
               
               //On active la pompe
               ActiverPompe();
             }
            digitalWrite(PIN_DEL, LOW);
             CptCycleNuit = 0;          
         }
         else
         {
            ++CptCycleNuit; 
            digitalWrite(PIN_DEL, HIGH);
               MillisecondesEcoulees = 0;
         }   
     }  
                
     TFTscreen.stroke(0,0,0);
     TFTscreen.text("Arrosage ",0 , 90);
}

//Fonction qui vérifie si le temps est venu d'arroser à nouveau
boolean VerifierSiTempsEcoule()
{
  //si le temps écoulé est égal ou à dépasser l'interval d'arrosage
  return (MillisecondesEcoulees >= INTERVAL_ARROSAGE * NB_MINUTES);
}

unsigned long CalculerSoleil()
{
    unsigned long soleil = analogRead(PIN_SOLEIL);
    return map(soleil,0, SOLEIL_MAX, 0 , 100);
}

//Fonction qui vérifie si la chaleur est adéquate pour arroser
unsigned long CalculerChaleur()
{
  unsigned long temp = analogRead(PIN_TEMPERATURE);
    return     map(temp, 0, TEMPERATURE_MAX, 0 , 100);
}

void VerifierHumidite()
{
    //Capteur D'humidité!!
}

void Arroser()
{
   //Si on  arrose, on affiche qu'on arrose! 
   //Serial.println("Les plantes ont soif depuis (sec) : " + (MillisecondesEcoulees / NB_MILLISECONDES));
   int seconde = MillisecondesEcoulees / NB_MILLISECONDES;
     String temps = String(seconde);
     temps.toCharArray(tempsArrosage, 6);
      TFTscreen.stroke(0,255,0);
      TFTscreen.text("Arrosage ",0 , 90);
      TFTscreen.text(tempsArrosage ,0 , 110);
      
     
     

   
   //On vérifie si on continue à arroser, donc si on a dépassé l'intervall d'arrosage
   if(MillisecondesEcoulees >= DUREE_ARROSAGE * NB_MILLISECONDES)
   {
      //si l'arrosage est complèté, on désactive la pin de la pompe
      DesactiverPompe();
      
      //on recalcule le temps prochain de l'intervale et la durée de l'Arrosage
   }      
}

void CalculerParametresArrosage()
{
   //Calcul de la durée
   unsigned long tempCour = CalculerChaleur();
   unsigned long soleilCour = CalculerSoleil();
   
   if(tempCour > 30)
   {
     Interval = 30;
   }
   else
   {
     if(tempCour > 18)
     {
       Interval = 60 * ( 1 - ( (1.0f/24.0f) * (tempCour - 18)));
     }
     else
     {
      Interval = 60;
     }
   }
   
   if(soleilCour > 80)
   {
     Duree = 50;     
   }
   else
   {
     if(soleilCour > 20)
     {
       Duree = 50 * ( 1 - (( 1.0f /100.0f) * (soleilCour - 20)));
     } 
     else
     {
      Duree = 0; 
     }
   }
}

void ActiverPompe()
{
   //On met l'état de la pin à HIGH et on réécrit la nouvelle valeur dans la pin
   EstEnTrainDArroser = true;
   Serial.println("Activation de la pompe ...");
   EtatPompe = HIGH;
   digitalWrite(PIN_POMPE,EtatPompe);
   MillisecondesEcoulees = 0;
   MillisecondesPrecedent = 0;
}

void DesactiverPompe()
{
   //On met l'état de la pin à LOW et on réécrit la nouvelle valeur dans la pin
   EstEnTrainDArroser = false;
   Serial.println("Désactivation de la pompe ...");
   EtatPompe = LOW;
   digitalWrite(PIN_POMPE,EtatPompe);
   MillisecondesEcoulees = 0;
   MillisecondesPrecedent = 0;
}


