
// Fichier où se retrouve toutes les constantes à modifier selon les besoins


// Fichiers qui doivent être inclus
#include <Arduino.h>
#include <SimpleTimer.h>

// Défini pour les # de Pin. 'A' désigne les pins à lecture analogique.
#define PIN_SOLEIL A0
#define PIN_TEMPERATURE A1

#define PIN_DEL 2
#define PIN_EAU_BAS 3
#define PIN_ENGRAIS 5
#define PIN_POMPE 6


// Défini les pins pour l'écran
#define cs   10 // Arduino-Pin an Display CS   
#define dc   9  // Arduino-Pin an 
#define rst  8  // Arduino Reset-Pin

#define MAX_CARACTERES_PAR_LIGNES 100
#define MAX_LIGNES 5

// Define pour les mesures des capteurs
#define TEMPERATURE_MIN 18 //TODO : 18 degré Celsius, c'est quoi en V? 
#define TEMPERATURE_MAX 80
#define VAL_SOLEIL_MIN 80
#define SOLEIL_MAX 80
#define SOLEIL_MIN 20

// Define pour l'arrossage
#define DUREE_ARROSAGE 30           // La Durée d'Arrosage en secondes
#define INTERVAL_ARROSAGE 1        // L'intervalle entre chaque arrosage en minutes
#define DEBUT_ARROSAGE 0                    
#define TEMPS_ENGRAIS 5000          // Temps de la durée ou la pompe à engrais fonctionne en milliseconde


//Define pour la conversion du temps
#define NB_MS_IN_SECOND 1000              // Nombre de millisecondes dans une seconde
#define NB_MS_IN_MINUTE 60000             // Nombre de millisecondes dans une minutes

