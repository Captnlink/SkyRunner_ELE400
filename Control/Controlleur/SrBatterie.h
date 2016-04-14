/**
    @file SrBatterie.h
    @brief Contient la classe batterie

    @author Captnlink
    @date March 20, 2016
*/

#ifndef THERMISTANCE_H_
#define THERMISTANCE_H_

#include <Arduino.h>
#include "SrConfig.h"

/**
    @class Batterie SrBatterie.h
    @brief Permet l'acquisition d'une valeur de temperature et de voltage

    @author Captnlink

    @version 1.4
    @date April 14, 2016

	@warning Il y a un delai(10) (10 ms) dans la fonction GetSample().
	
	Permet de recuperer une valeur analogique et de la transformer en temperature ou voltage selon la pin utilise.
	La librairie utilise pour recuperer la temperature a ete originalement cree par Lady Ada.
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
