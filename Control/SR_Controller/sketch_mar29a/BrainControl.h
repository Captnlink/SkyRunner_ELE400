/**
    Project : CableCam_Chariot\n
    @file BrainControl.h
    @brief Gere le controle du moteur selon les interfaces externes

    @author Captnlink

    @version 1.9
    @date March 20, 2016

	Gere le moteur avec un PID et les informations receuillit par les capteurs afin de controller la vitesse
  maximal et courante

*/

#ifndef BRAINCONTROL_H_
#define BRAINCONTROL_H_

#include "SrEncodeur.h"
#include "SrBatterie.h"
#include "PidController.h"
#include "Sabertooth.h"
#include "Arduino.h"
#include "SrConfig.h"
#include "NewPing.h"

/**
    @class BrainControl BrainControl.h
    @brief Gere la securite automatique et le controle de la drive

    @author Captnlink
    @version 1.10
    @date March 30, 2016

    Gere le PID du controle de vitesse. Process les informations des capteurs et de l'interfaces
	afin d'envoyer a la drive une consigne en tension.

*/

class BrainControl
{
private:
	int mPositionActuel;  //Position du chariot sur le cable (cm)
	int mPositionMax;     //Position maximum du point de depart (Longueur de cable) (cm)
	int mVitesseActuel;   //Vitesse actuel du chariot en cm/sec
	int mVitesseVoulu;    //Vitesse voulu du chariot en cm/sec
	int mDistanceAvant;   //Distance vue par le capteur de distance avant
	int mDistanceArriere; //Distance vue par le capteur de distance arriere

    //127 = Vitesse Max avant
    //0  = Vitesse Null
    //-127   = Vitesse Max arriere
	double mOutputPID;
	int mAcceleration; // 0 = Max et 5 = Very Slow
	bool arretUrgence;

	PidController PID;  //PID pour la sortie vers la drive
	SrEncodeur Encodeur;
	Batterie mBatterie;
	Sabertooth SyrenDrive;
	NewPing CapteurDistanceAvant;
	NewPing CapteurDistanceArriere;
	

public:
    BrainControl(Sabertooth _SyrenDrive);

    /**
    @fn Update
    @brief Fait l'update des composante du controller

    Update la rampe d'acceleration, la vitesse de la drive.
    Gere les safety de position et de capteur
    Arret d'urgence
    */
    void Update();


	//Setters
	bool SetArretUrgenge();
	void SetVitesseVoulu(int _vitesseVoulu);
	void SetPositionMax(int _positionMax){mPositionMax = _positionMax;}
	bool SetAcceleration(int _acceleration);

	//Getters
    bool IsArretUrgence(){return arretUrgence;} const
	
	int GetVitesseVoulu(){return mVitesseVoulu;} const
	int GetVitesseActuel(){return mVitesseActuel;} const
	
	int GetPositionMax(){return mPositionMax;} const
	int GetPositionActuel(){return mPositionActuel;} const
	
	int GetDistanceAvant(){return mDistanceAvant;} const
	int GetDistanceArriere(){return mDistanceArriere;} const
	
	int GetAcceleration(){return mAcceleration;} const

	double GetTemperatureBaterie(){return mBatterie.GetTempratureCelsius();} 
	double GetTensionBaterie(){return mBatterie.GetVoltage();}  
};

#endif
