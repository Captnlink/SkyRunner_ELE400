/**
    Project : CableCam_Chariot\n
    @file BrainControl.h
    @brief G�re le contr�le du moteur selon les interfaces externes

    @author Captnlink
	
    @version 1.0
    @date March 20, 2016

	G�re le moteur avec un PID et les informations receuillit par les capteurs (autres classes)
	
*/

#ifndef BRAINCONTROL_H_
#define BRAINCONTROL_H_


/**
    @class BrainControl BrainControl.h
    @brief g�re l'�tat de la LED d'information

    @author Captnlink
    @version 1.1
    @date March 20, 2016

    G�re le PID du controle de vitesse. Process les informations des capteurs et de l'interfaces
	afin d'envoyer � la drive une consigne en tension.
	
*/
class BrainControl
{
private:
    //Mettre dans le .h des default config, un enum pour chaque possibilit� d'erreur
	
	int directionChariotActuel; 
	int directionChariotVoulu; 
	double distance; //Distance du chariot sur le cable
	double distanceMax; //Distance maximum du point de d�part (Longueur de cable)
	double vitesseActuel;
	double vitesseVoulu;
	
	//Accel/Decel (0 a 5) 
	int acceleration; // 0 = None et 5 = Max
	int decceleration; // 0 = Max et 5 = None
	
public:
    BrainControl();

	
	//Setters
	void SetVitesseVoulu();
	void SetDistanceMax

	//Getters

private:
    /**
    @fn CalculPosition
    @brief Fait le calcul de position selon la direction et les pulses par revolution
    @param [NAME] : Param�tre de la founction
    @return double en m�tres

    */
	double CalculPosition(/*directionChariotActuel + directionChariotVoulu*/);
	
}

#endif