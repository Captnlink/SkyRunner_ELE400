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

#include "SrEncodeur.h"
#include "SrBatterie.h"
#include "PidController.h"
#include "Sabertooth.h"
#include "Arduino.h"

#define MAX_POSITION_LV_4 400 //En cm pour la distance ou la position
#define MAX_POSITION_LV_3 300 //En cm
#define MAX_POSITION_LV_2 200 //En cm
#define MAX_POSITION_LV_1 100 //En cm

#define MAX_VITESSE_4 40
#define MAX_VITESSE_3 30
#define MAX_VITESSE_2 20
#define MAX_VITESSE_1 10


/**
    @class BrainControl BrainControl.h
    @brief Gere la securite automatique et le controle de la drive

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

	int mPositionActuel; //Position du chariot sur le cable (cm)
	int mPositionMax; //Position maximum du point de d�part (Longueur de cable) (cm)
	int mVitesseActuel; // en cm/sec
	int mVitesseVoulu;// en cm/sec
  int mDistanceAvant;  //Distance vue par le capteur de distance avant
	int mDistanceArriere;//Distance vue par le capteur de distance arriere


    //127 = Vitesse Max avant
    //0  = Vitesse Null
    //-127   = Vitesse Max arriere
	double mOutputPID;

	int mAcceleration; // 0 = Max et 5 = Very Slow

	bool arretUrgence;

	PidController PID;
	SrEncodeur Encodeur;
  Batterie mBatterie;
  Sabertooth SyrenDrive;//127 is Serial address de la drive

public:
    BrainControl();

    /**
    @fn Update
    @brief Fait l'update des composante du controller

    Update la rampe d'acceleration, la vitesse de la drive.
    Gere les safety de position et de capteur
    Arret d'urgence
    */
    void Update();

    bool SetArretUrgenge();
    bool IsArretUrgence(){return arretUrgence;}

	//Setters
	void SetVitesseVoulu(int _vitesseVoulu);
	void SetPositionMax(int _positionMax){mPositionMax = _positionMax;}

	bool SetAcceleration(int _acceleration);

	//Getters
	int GetVitesseVoulu(){return mVitesseVoulu;}
	int GetVitesseActuel(){return mVitesseActuel;}

	int GetPositionMax(){return mPositionMax;}
	int GetPositionActuel(){return mPositionActuel;}

	int GetAcceleration(){return mAcceleration;}

	double GetTemperatureBaterie(){return mBatterie.GetTempratureCelsius();}
	double GetTensionBaterie(){return mBatterie.GetVoltage();}

private:
    /**
    @fn CalculPosition
    @brief Fait le calcul de position selon la direction et les pulses par revolution
    @param [NAME] : Param�tre de la founction
    @return double en m�tres

    */
};

#endif
