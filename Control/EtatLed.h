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
	
	bool ledActualState; //�tat de la LED (Allum� ou �teinte)
	char controllerState; //�tat du controlleur
	
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
	bool SetGood();
	bool SetBattFaible();
	bool SetBattTooHot();
	bool SetObjectDetected();
	bool SetEndOfCourse();
	bool SetCantGoSetPoint();
	bool SetEmergencyStop();
	bool SetNoComms();
}

#endif