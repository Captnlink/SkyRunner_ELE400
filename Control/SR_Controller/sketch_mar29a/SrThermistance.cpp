#include "SrThermistance.h"


Thermistance::Thermistance(){}

// Get an average samples
void Thermistance::GetSample(){
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
 void Thermistance::ConvertAnalogueToResistance(){

	average = 1023 / average - 1;
	average = SERIESRESISTOR / average;
 }

   // convert the resistance value to celcius
 void Thermistance::ConvertResistanceToCelcius(){

	steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;
 }

  double Thermistance::GetTempratureCelsius(){

	 GetSample();
	 ConvertAnalogueToResistance();
	ConvertResistanceToCelcius();

 }
