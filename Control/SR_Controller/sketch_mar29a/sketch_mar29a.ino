#include "BrainControl.h"
#include "SrEncodeur.h"
#include "SrConfig.h"

//Creation d'un port de communication serie software
SoftwareSerial mySerial(10, 11); // RX, TX

//Creation objet Drive
Sabertooth SyrenDrive(SYREN_DRIVE_ADDR,mySerial);

//Creation objet du controlleur de la drive
//On passe en parametre l'objet Drive
BrainControl Controlleur(SyrenDrive);

void setup() {
  Controlleur.SetPositionMax(1000); //Longeur du cable 1000 cm

  Serial.begin(9600);   //Communication Serie Hardware - XBee
  mySerial.begin(9600); //Communication Serie Software - Drive
}

void loop() {
  //Update du controlleur
  Controlleur.Update();

  //Code du main ICI
  double temp   = Controlleur.GetTemperatureBaterie();
  double volt   = Controlleur.GetTensionBaterie();
  //double vitesse   = Controlleur.GetVitesseActuel();
  int _position = Controlleur.GetPositionActuel();

  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Voltage     = ");
  Serial.println(volt);
  //Serial.print("Vitesse     = ");
  //Serial.println(vitesse);
  Serial.print("Position    = ");
  Serial.println(_position);
  delay(600);
}

