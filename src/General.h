
// Fichier où se retrouve toutes les constantes à modifier selon les besoins


// Fichiers qui doivent être inclus
#include <Arduino.h>
#include <SimpleTimer.h>

#include <TFT.h>    // Core graphics library
#include <SPI.h>

// Défini pour les # de Pin. 'A' désigne les pins à lecture analogique.
//#define PIN_SOLEIL A0


#define PIN_DEL 2
#define PIN_EAU_BAS 3
#define PIN_ENGRAIS 5
#define PIN_POMPE_GROUND 38
#define PIN_POMPE 39
#define PIN_CAPTEUR 35
#define PIN_PHOTO_RESISTANCE A1


#define cs   53 // Arduino-Pin an Display CS   
#define dc   49  // Arduino-Pin an 
#define rst  48  
// Arduino Reset-Pin*/

#define MAX_CARACTERES_PAR_LIGNES 100
#define MAX_LIGNES 4

// Define pour les mesures des capteurs
#define TEMPERATURE_MIN 20
#define TEMPERATURE_MAX 30  
#define DUREE_MIN 30        // en secondes
#define DUREE_MAX 60

#define SOLEIL_MAX 100
#define SOLEIL_MIN 50
#define INTERVAL_MIN 30     // En minutes
#define INTERVAL_MAX 60

// Define pour l'arrossage
#define DUREE_ARROSAGE 60           // La Durée d'Arrosage en secondes
#define INTERVAL_ARROSAGE 1        // L'intervalle entre chaque arrosage en minutes


//Define pour la conversion du temps
#define NB_MS_IN_SECOND 1000              // Nombre de millisecondes dans une seconde
#define NB_MS_IN_MINUTE 60000             // Nombre de millisecondes dans une minutes

