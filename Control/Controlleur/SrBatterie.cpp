#include "SrBatterie.h"


Batterie::Batterie(){}

// Get an average samples
void Batterie::GetSample(int _SensorPin){
// take N samples in a row, with a slight delay
  for (i=0; i < NUMSAMPLES; i++) {
   samples[i] = analogRead(_SensorPin); //THERMISTORPIN
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

	GetSample(THERMISTORPIN);
	ConvertAnalogueToResistance();
	ConvertResistanceToCelcius();

 }

 double Batterie::GetVoltage(){
	 GetSample(DIVISEUR_TENSION_PIN);
	 return average * DIVISEUR_TENSION_MAX / 1023;
	 
 }