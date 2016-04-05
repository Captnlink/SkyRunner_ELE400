/**
    Project : CableCam_Chariot\n
    @file EtatLed.h
    @brief G�rent la LED d'information selon les erreurs et warnings du systeme

    @author Captnlink
	@author Wsimon
	
    @version 1.0
    @date March 20, 2016

	Afin de visualiser les probl�mes pouvant survenir � l'int�rieur du controlleur
	et les �tats � probl�mes, cette class permet donc de g�rer la LED.
	
*/

#ifndef EtatLed_H_
#define EtatLed_H_

#include "SrConfig.h"
#include "Arduino.h"

/**
    @class EtatLed EtatLed.h
    @brief g�re l'�tat de la LED d'information

    @author Captnlink
    @version 1.1
    @date March 20, 2016

    Permet de g�rer les informations du controlleur qui peuvent �tre afficher par la LED.
	
*/
class EtatLed
{
private:
    //Mettre dans le .h des default config, un enum pour chaque possibilit� d'erreur
	
	int flashLedState; //�tat de la LED 
	int errorState;    //�tat de la destion d'erreur 
	int oldTime;    //�tat de la destion d'erreur 
	char controllerState; //�tat du controlleur Binary state
	
	void ChangeLedColor(int color);
	
public:
    EtatLed();

    /**
    @fn UpdateLedState
    @brief cette m�thode refresh l'�tat de la LED
    @param [NAME] : Param�tre de la founction
    @return output   : true = Success, false = fail.
	
    The controller use proportional, integral and derivative operation to drive an output

    */
	bool UpdateLedState(/*State of Controler*/);
	
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
};

#endif
