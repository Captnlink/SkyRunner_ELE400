/**
    Project : CableCam_Chariot\n
    @file SrBatterie.h
    @brief Recupere la temperature de la thermistance et la tension de la batterie

    @author Captnlink

    @version 1.3
    @date March 20, 2016

    @warning Il y a un delai(10) (10 ms) dans la fonction GetSample().
    Il serai important de trouver un autre moyen de faire l'acquisition des donnees
*/

#ifndef THERMISTANCE_H_
#define THERMISTANCE_H_

#include <Arduino.h>
#include "SrConfig.h"

/**
    @class Batterie SrBatterie.h
    @brief Permet l'acquisition d'une valeur de temperature

    @author Captnlink

    @version 1.3
    @date March 20, 2016

	  La librairie a ete originalement cree par Lady Ada
*/
class Batterie
{
public:
    Batterie();

    /**
    @fn GetTempratureCelsius
    @brief Recupere la temperature en degree C
    @return double Temperature degree C
    */
	double GetTempratureCelsius();
	/**
    @fn GetVoltage
    @brief Recupere la tension de la batterie
	@return double Tension 0-5v
    */
	double GetVoltage();

private:
	int i;
	double average;
	int samples[NUMSAMPLES];
	double steinhart;

	void GetSample(int _SensorPin);
	void ConvertAnalogueToResistance();
	void ConvertResistanceToCelcius();
};

#endif
