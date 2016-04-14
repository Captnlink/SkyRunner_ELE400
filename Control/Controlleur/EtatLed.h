/**
    Project : CableCam_Chariot\n
    @file EtatLed.h
    @brief Gerent la LED d'information selon les erreurs et warnings du systeme

    @author Captnlink
	@author Wsimon

	Afin de visualiser les problemes pouvant survenir a l'interieur du controlleur
	et les etats a problemes, cette class permet donc de gerer la LED.
	
*/

#ifndef EtatLed_H_
#define EtatLed_H_

#include "SrConfig.h"
#include "Arduino.h"

/**
    @class EtatLed EtatLed.h
    @brief gere l'etat de la LED d'information

    @author Captnlink
    @version 1.3
    @date April 14, 2016

    Permet de gerer les informations du controlleur qui peuvent �tre afficher par la LED.
	
*/
class EtatLed
{
public:
    EtatLed();

    /**
    @fn UpdateLedState
    @brief cette methode refresh l'etat de la LED
    @return output   : true = Success, false = fail.
	
    */
	bool UpdateLedState();
	
	//Setters
	bool SetGood(bool state);
	bool SetBattFaible(double tension_batteriee);
	bool SetBattTooHot(double tempBatterie);
	bool SetObjectDetected(int distanceObjetDetecteAvant, int distanceObjetDetecteArriere);
	bool SetEndOfCourse(int positionActuel, int PositionMax);
	bool SetCantGoSetPoint(int vitesseActuel, int vitesseVoulu);
	bool SetEmergencyStop(bool state);
	bool SetNoComms(bool state);

  //Getters
  char GetErrorState(){return controllerState;}
private:
    //Mettre dans le .h des default config, un enum pour chaque possibilit� d'erreur
	
	int flashLedState; //�tat de la LED 
	int errorState;    //�tat de la destion d'erreur 
	int oldTime;    //�tat de la destion d'erreur 
	char controllerState; //�tat du controlleur Binary state
	
	void ChangeLedColor(int color);
};

#endif
