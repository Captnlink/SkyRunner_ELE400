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


#include "Batterie.h"
Batterie::Batterie(){}

// Get an average samples
void Batterie::GetSample(){
// take N samples in a row, with a slight delay
  for (i=0; i < NUMSAMPLES; i++) {
   samples[i] = analogRead(THERMISTORPIN);
   delay(10);
 }
   // average all the samples out
  average = 0;
  for (i=0; i <  NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
}

  // convert the average value to resistance
 void Batterie::ConvertAnalogueToResistance(){

	average = 1023 / average - 1;
	average = SERIESRESISTOR / average;
 }

   // convert the resistance value to celcius
 void Batterie::ConvertResistanceToCelcius(){

	steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;
 }

  double Batterie::GetTempratureCelsius(){

	 GetSample();
	 ConvertAnalogueToResistance();
	ConvertResistanceToCelcius();

 }



  double Batterie:: GetTension()
{
	
	 echantillons=0;
	 moyenne=0;
	voltage=0;

  // take N samples in a row, with a slight delay

	/* Tester la lecture de donnée avec arduino
  for (i=0; i< NB_ECHANTILLON_TENSION ; i++)
  {
   echantillons= echantillons+analogRead(PIN_BATTERIE_TENSION);
   delay(10);
  }
	moyenne=echantillons/NB_ECHANTILLON_TENSION;
	*/
	/* la formule permet de convertir la valeur envoyé par arduino de 0 a 1023, a une valeur
	entre la tension maximum de la batterie mesurée et  la valeur de la tension quand la batterie mesurée est épuisé  .*/


  voltage=(((moyenne/1023)*(TENSION_BATTERIE_MAX)));// voltage entre 0 et 15 V(Tension_BAtterie_max)

	if(voltage<TENSION_BATTERIE_EPUISE)
	{
		voltage=0;
	}
	else if(voltage>TENSION_BATTERIE_MAX)
	{
		voltage = 100;
	}
	else if(voltage>TENSION_BATTERIE_EPUISE & voltage<TENSION_BATTERIE_MAX)
	{
		voltage = (voltage-TENSION_BATTERIE_EPUISE)/(TENSION_BATTERIE_MAX-TENSION_BATTERIE_EPUISE)*100;
	}



}
