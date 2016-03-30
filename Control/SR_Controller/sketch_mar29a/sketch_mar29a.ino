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

  Controlleur.GetTemperatureBaterie();
  Controlleur.GetTensionBaterie();
}
