/**
    Project : CableCam_Chariot\n
    @file EtatLed.h
    @brief Gèrent la LED d'information selon les erreurs et warnings du systeme

    @author Captnlink
	@author Wsimon
	
    @version 1.0
    @date March 20, 2016

	Afin de visualiser les problèmes pouvant survenir à l'intérieur du controlleur
	et les états à problèmes, cette class permet donc de gérer la LED.
	
*/

#ifndef EtatLed_H_
#define EtatLed_H_


/**
    @class EtatLed EtatLed.h
    @brief gère l'état de la LED d'information

    @author Captnlink
    @version 1.1
    @date March 20, 2016

    Permet de gérer les informations du controlleur qui peuvent être afficher par la LED.
	
*/
class EtatLed
{
private:
    //Mettre dans le .h des default config, un enum pour chaque possibilité d'erreur
	
	int flashLedState; //État de la LED 
	int errorState;    //État de la destion d'erreur 
	int oldTime;    //État de la destion d'erreur 
	unsigned int controllerState; //État du controlleur Binary state
	
	void ChangeLedColor(int color);
	
public:
    EtatLed();

    /**
    @fn UpdateLedState
    @brief cette méthode refresh l'état de la LED
    @param [NAME] : Paramètre de la founction
    @return output   : true = Success, false = fail.
	
    The controller use proportional, integral and derivative operation to drive an output

    */
	bool UpdateLedState(/*State of Controler*/);
	
	//Setters
	bool SetGood(bool state);
	bool SetBattFaible(double tension_batteriee);
	bool SetBattTooHot(double tempBatterie);
	bool SetObjectDetected(int distanceObjetDetecte);
	bool SetEndOfCourse(bool state);
	bool SetCantGoSetPoint(bool state);
	bool SetEmergencyStop(bool state);
	bool SetNoComms(bool state);
}

#endif