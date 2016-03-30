/**
    Project : CableCam_Chariot\n
    @file Thermistance.h
    @brief Recupere la temperature de la thermistance

    @author Captnlink

    @version 1.0
    @date March 20, 2016

    @warning Il y a un delai(10) (10 ms) dans la fonction GetSample().
    Il serai important de trouver un autre moyen de faire l'acquisition des donnees
*/

#ifndef THERMISTANCE_H_
#define THERMISTANCE_H_

#include <Arduino.h>

#define THERMISTORPIN A0   // Pin analogique du arduino
#define THERMISTORNOMINAL 10000  // resistance a 25 degrees C
#define TEMPERATURENOMINAL 25  // temp. pour resistance nominal (almost always 25 C)
#define NUMSAMPLES 5 // Nombre d'echantillonage pour la moyenne, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950 // Coefficient Beta de la thermistance (normalement 3000-4000)
#define SERIESRESISTOR 10000  // La valeur 'l'autre' resistance

/**
    @class Thermistance Thermistance.h
    @brief Permet l'acquisition d'une valeur de temperature

    @author Captnlink

    @version 1.1
    @date March 20, 2016

	La librairie a ete originalement cree par Lady Ada
*/
class Thermistance
{
public:
    Thermistance();

    /**
    @fn GetTempratureCelsius
    @brief Recupere la temperature en degree C
    @return double Temperature degree C
    */
	double GetTempratureCelsius();

private:
	int i;
	double average;
	int samples[NUMSAMPLES];
	double steinhart;

	void GetSample();
	void ConvertAnalogueToResistance();
	void ConvertResistanceToCelcius();
};

#endif
