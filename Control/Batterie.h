/**
    Project : CableCam_Chariot\n
    @file Batterie.h
    @brief Recupere la temperature de la thermistance et la tension

    @author Captnlink
	modifié par Wsimon

    @version 1.0
    @date March 29, 2016

    @warning Il y a un delai(10) (10 ms) dans la fonction GetSample().
    Il serai important de trouver un autre moyen de faire l'acquisition des donnees
*/

#ifndef OK_BATTERIE // pour empecher la double-compilation 
#define OK_BATTERIE 

#include <Arduino.h>

#define THERMISTORPIN A0   // Pin analogique du arduino
#define THERMISTORNOMINAL 10000  // resistance a 25 degrees C
#define TEMPERATURENOMINAL 25  // temp. pour resistance nominal (almost always 25 C)
#define NUMSAMPLES 5 // Nombre d'echantillonage pour la moyenne, more takes longer but is more 'smooth'
#define BCOEFFICIENT 3950 // Coefficient Beta de la thermistance (normalement 3000-4000)
#define SERIESRESISTOR 10000  // La valeur 'l'autre' resistance



#define PIN_DIVISEUR_TENSION 2
//valeur pour le calcul de la tension
#define NB_ECHANTILLON_TENSION 5  //quantité d'échantillon pour renvoyer la valeur de la tension
#define TENSION_BATTERIE_MAX 15 //Valeur de la tension maximum de la batterie a mesuré
#define TENSION_BATTERIE_FAIBLE 12 //Valeur de la tension où on considère que la batterie a mesuré est faible
#define TENSION_BATTERIE_EPUISE 11 //Valeur de la tension où on considère que la batterie a mesuré est épuisé

/**
    @class Thermistance Thermistance.h
    @brief Permet l'acquisition d'une valeur de temperature

    @author Captnlink

    @version 1.1
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
    @fn GetTension e
    @brief Recupere la tension en volt et retoune une valeur en pourcentage
    @return double tension en pourcentage
    */
	double GetTension();

private:
	int i;
	double average;
	int samples[NUMSAMPLES];
	double steinhart;

	void GetSample();
	void ConvertAnalogueToResistance();
	void ConvertResistanceToCelcius();

	int i;
	double echantillons;
	double moyenne;
	double voltage;
};

#endif
