/*! \mainpage Controle de chariot pour camera sur cable
 *
 * \section team_sec Presentation
 *
 * L'equipe est SkyRunner. Nous somme un groupe d'etudiant de l'ecole de technologie superieur.
 * Dans le but de notre cours ELE400 - Methodologie de design, nous devons develloper une technologie
 * pour un client. Notre mandat, offert par Tribor Design, est de faire un chariot de camera sur cable
 * repondant a certain critere de securite en plus de faire de la recherche sur diffente technologie pouvant accomplir
 * les besoins du client./n/n
 *
 * L'equipe est compose de 8 etudiants en genie electrique./n
 * Gestionnaire d'equipe - Samuel Geoffroy-heroux AKA CaptnLink/n
 * Coordonateur des communication externe et ingenieur chef du module controle - Antoine Champoux AKA antoine0670/n
 * Coordonateur des achats - David Prairie-Bourgoult AKA purepp666/n
 * Chef ingenieur du module interface - Alexi Demers AKA aledemers/n
 * Chef ingenieur du module communication - Danny Arseneau AKA dannyarseneau/n
 * Chef ingenieur du montage mechanique et electrique - Marc-Daniel Paul/n
 * Ingenieur - Ka Hey Chu AKA khchu1993/n
 * Ingenieur - Wantel Simon AKA Wsmon/n
 *
 */
 
/**
 * 	\section PinOut_sec E/S du Controlleur
 *	# SERIAL PIN XBEE 0
 *	# SERIAL PIN XBEE 1
 *	# ENCODEUR_PIN_A 2
 *	# ENCODEUR_PIN_B 3
 *	# PIN_LD_GREEN 4
 *	# PIN_LD_RED 5
 *	# SYREN_PIN_TX 10
 *	# SYREN_PIN_RX 11
 *	# TRIGGER_PIN_AVANT  6
 *	# TRIGGER_PIN_ARRIERE  8
 *	# ECHO_PIN_AVANT     7
 *	# ECHO_PIN_ARRIERE     9
  */

//Example of comment
/*
 *	@class Name (@fn, @file, @var)
 *	@brief Description
 *
 *	@author Captnlink
 *	@email samuel.geoffroy.92@gmail.com
 *	@version 0.0
 *	@date March 20, 2016
 *	@param feedback: feedback from machinery
 *	@return output: Percentage of output
 *
 *	Detailed Description
*/
 
#ifndef SRCONFIG_H_
#define SRCONFIG_H_

#include "SoftwareSerial.h"

#define DEBUG 1

//Choix de Pins
//SERIAL PIN XBEE 0
//SERIAL PIN XBEE 1
#define ENCODEUR_PIN_A 2
#define ENCODEUR_PIN_B 3
#define PIN_LD_GREEN 4
#define PIN_LD_RED 5
#define SYREN_PIN_TX 10
#define SYREN_PIN_RX 11
#define TRIGGER_PIN_AVANT  6
#define TRIGGER_PIN_ARRIERE  8
#define ECHO_PIN_AVANT     7
#define ECHO_PIN_ARRIERE     9

#define THERMISTORPIN A0   // Pin analogique du arduino
#define DIVISEUR_TENSION_PIN A1   // Pin analogique du arduino

//BrainControl
#define MAX_DISTANCE 500 //Capteur

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
#define THERMISTORNOMINAL 10000  // resistance a 25 degrees C
#define TEMPERATURENOMINAL 25  // temp. pour resistance nominal (almost always 25 C)
#define NUMSAMPLES 5 // Nombre d'echantillonage pour la moyenne, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950 // Coefficient Beta de la thermistance (normalement 3000-4000)
#define SERIESRESISTOR 10000  // La valeur 'l'autre' resistance

//Encodeur
#define SAMPLEVITESSE 5
#define RAYONCM 5

//PID Controller
#define PROPORTIONAL_GAIN 1
#define INTEGRAL_GAIN 0
#define DERIVATIVE_GAIN 0

//Parametre par default
#define DEFAULT_VITESSE_VOULU 0
#define DEFAULT_ACCELERATION 0
#define DEFAULT_POSITION_MAX 0

#define DIVISEUR_TENSION_MAX 15   // Tension maximal du diviseur de tension
#define BATTERIE_LOW 12
#define TEMP_BATT_TOO_HOT 40

//D�lai du cycle pour regarder l'�tat des led et aussi d�lai de  clignotement
#define DELAY_ETAT_LED 250

//fausse Enumeration coleur LED 
#define GREEN 1
#define RED 2
#define YELLOW 3
#define NO_LIGHT 4

//Binaire des etats d'erreurs
#define STATE_GOOD 0
#define STATE_LOWBATT 4
#define STATE_HOTBATT 2
#define STATE_OBJDETECT 32
#define STATE_ENDCOURSE 1
#define STATE_NOSETPOINT 8
#define STATE_EMERGENCY 64
#define STATE_NOCOMMS 128

#endif
