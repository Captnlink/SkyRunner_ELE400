#ifndef SRCONFIG_H_
#define SRCONFIG_H_

#include "SoftwareSerial.h"

//BrainControl
#define MAX_POSITION_LV_5 500 //En cm pour la distance ou la position
#define MAX_POSITION_LV_4 400 //En cm
#define MAX_POSITION_LV_3 300 //En cm
#define MAX_POSITION_LV_2 200 //En cm
#define MAX_POSITION_LV_1 100 //En cm

#define MAX_VITESSE_4 40
#define MAX_VITESSE_3 30
#define MAX_VITESSE_2 20
#define MAX_VITESSE_1 10

#define SYREN_DRIVE_ADDR 127


//Batterie
#define THERMISTORPIN A0   // Pin analogique du arduino
#define THERMISTORNOMINAL 10000  // resistance a 25 degrees C
#define TEMPERATURENOMINAL 25  // temp. pour resistance nominal (almost always 25 C)
#define NUMSAMPLES 5 // Nombre d'echantillonage pour la moyenne, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950 // Coefficient Beta de la thermistance (normalement 3000-4000)
#define SERIESRESISTOR 10000  // La valeur 'l'autre' resistance

#define DIVISEUR_TENSION_PIN A1   // Pin analogique du arduino
#define DIVISEUR_TENSION_MAX 15   // Tension maximal du diviseur de tension

//Encodeur
#define SAMPLEVITESSE 5
#define RAYONCM 5


#endif
