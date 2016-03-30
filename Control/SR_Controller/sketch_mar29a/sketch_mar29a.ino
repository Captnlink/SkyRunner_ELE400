#include "BrainControl.h"

BrainControl Controlleur;

void setup() {
  // put your setup code here, to run once:
  Controlleur.SetPositionMax(1000); //Longeur du cable 1000 cm
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Controlleur.Update();

  double temp   = Controlleur.GetTemperatureBaterie();
  double volt   = Controlleur.GetTensionBaterie();
  int vitesse   = Controlleur.GetVitesseActuel();
  int _position = Controlleur.GetPositionActuel();

  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Voltage     = ");
  Serial.println(volt);
  Serial.print("Vitesse     = ");
  Serial.println(vitesse);
  Serial.print("Position    = ");
  Serial.println(_position);
}

