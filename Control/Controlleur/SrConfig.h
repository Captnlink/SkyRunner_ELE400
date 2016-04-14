
 //Example of comment
 /*

    @class Name (@fn, @file, @var)
    @brief Description

    @author Captnlink
	@email samuel.geoffroy.92@gmail.com
    @version 0.0
    @date March 20, 2016
    @param feedback: feedback from machinery
    @return output: Percentage of output
	
    Detailed Description
*/
 
/*
Tram de connection addr:122
CXNzc

Tram de Deconexion addr:122
DCXzY

Tram de config addr:122 accel:121 Longeur 12048
CNFzyx0r

Tram de control addr:122 vit:122 ArretDurgence:122
CNTzzzS
*/
 
#ifndef SRCONFIG_H_
#define SRCONFIG_H_

#include "SoftwareSerial.h"

#define DEBUG 0

//Choix de Pins
//Pins Digitales
//SERIAL PIN XBEE 0
//SERIAL PIN XBEE 1
#define ENCODEUR_PIN_A 2
#define ENCODEUR_PIN_B 3
#define PIN_LD_GREEN 4
#define PIN_LD_RED 5
#define SYREN_PIN_TX 6
#define SYREN_PIN_RX 9
#define PIN_ARRET_URGENCE 7
#define TRIGGER_PIN_AVANT  12
#define TRIGGER_PIN_ARRIERE  13
#define ECHO_PIN_AVANT     10
#define ECHO_PIN_ARRIERE     11

//Pins analogiques
#define THERMISTORPIN A0   			
#define DIVISEUR_TENSION_PIN A1   	

//BrainControl

//Les distances sont en Cm
//Capteur
#define MAX_DISTANCE 500 

//Distance de detection obstacle et de fin de course
#define MAX_POSITION_LV_5 150	//Non-utilise
#define MAX_POSITION_LV_4 120	//Non-utilise 
#define MAX_POSITION_LV_3 90	//Non-utilise
#define MAX_POSITION_LV_2 60	//Non-utilise
#define MAX_POSITION_LV_1 30	//Non-utilise 

//Difinition des vitesse maximum selon les positions et distances percu
#define MAX_VITESSE_4 40	//Non-utilise
#define MAX_VITESSE_3 30	//Non-utilise
#define MAX_VITESSE_2 20	//Non-utilise
#define MAX_VITESSE_1 10	//Non-utilise

//Adresse de la drive
#define SYREN_DRIVE_ADDR 128

//Batterie
//Non-utilise
#define THERMISTORNOMINAL 10000.0  // resistance de thermistance a 25 degrees C
#define TEMPERATURENOMINAL 25.0  // temp. pour resistance nominal (almost always 25 C)
#define NUMSAMPLES 5 // Nombre d'echantillonage pour la moyenne, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950.0 // Coefficient Beta de la thermistance (normalement 3000-4000)

//Valeur de la resistance pour la transformation ADC a resistance
#define SERIESRESISTOR 9000.0  // La valeur 'l'autre' resistance

//Encodeur
#define SAMPLEVITESSE 5
#define RAYONCM 0.055

//PID Controller
#define PROPORTIONAL_GAIN 0.1
#define INTEGRAL_GAIN 0.01
#define DERIVATIVE_GAIN 0

//Parametre par default
#define DEFAULT_VITESSE_VOULU 0
#define DEFAULT_ACCELERATION 0
#define DEFAULT_POSITION_MAX 0

#define DIVISEUR_TENSION_MAX 15   	// Tension maximal du diviseur de tension 
#define BATTERIE_LOW 10				// Pourcentage de batterie considerer faible
#define TEMP_BATT_TOO_HOT 30.0		// Seuil de temperature trop haute 

//Delai du cycle pour regarder l'etat des led et aussi delai de clignotement en milliseconde
#define DELAY_ETAT_LED 500

//Delai de la transmission de donnees par le XBee en milliseconde
#define DELAY_SEND_TRAM 100 

// Statut des led pour les switch case pour fonction etat-led
#define GREEN 1
#define RED 2
#define YELLOW 3
#define NO_LIGHT 4

//Valeur en binaire de la variable d'etat des Leds
#define STATE_GOOD 0
#define STATE_ENDCOURSE 1
#define STATE_HOTBATT 2
#define STATE_LOWBATT 4
#define STATE_NOSETPOINT 8

#define STATE_OBJDETECT 32
#define STATE_EMERGENCY 64
#define STATE_NOCOMMS 128

#endif
