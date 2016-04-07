/**
 * 
 * @author CaptnLink
 * @email  samuel.geoffroy.92@gmail.com
 * 
 * @author Wsmon
 * @email  
 * 
 * @author khchu
 * @email  
 * 
 * @author Antoine Champoux
 * @email  
 * @ide    Arduino IDE 1.6.7
 */

/*
Tram de connection addr:122
CXNzc

Tram de Deconexion addr:122
DCXzY

Tram de config addr:122 accel:121 Longeur 12048
CNFzyx0r

Tram de control addr:122 vit:122 ArretDurgence:122
CNTzzzS
*/



#include "SrBrainControl.h"
#include "SrEncodeur.h"
#include "SrConfig.h"
#include "SrCommunication.h"

//Creation d'un port de communication serie software
SoftwareSerial mySerial(SYREN_PIN_RX, SYREN_PIN_TX); // RX, TX

//Creation objet Drive
Sabertooth SyrenDrive(SYREN_DRIVE_ADDR,mySerial);

//Creation objet du controlleur de la drive
//On passe en parametre l'objet Drive
BrainControl Controlleur(SyrenDrive);

//Creation objet Communication
CommXBee Xbee(Controlleur);

//Creation objet Leds
EtatLed LED;

long oldTimeTransmition = 0;
long oldTimeState = 0;
void setup() {
  Serial.begin(9600);   //Communication Serie Hardware - XBee
  mySerial.begin(9600); //Communication Serie Software - Drive
}

void loop() {
  //Update du controlleur
  Controlleur.Update();
  
  Xbee.ReceiveTramXbee(Controlleur);
  
  long newTime = millis();
  if(newTime > (oldTimeState + 100)){

    LED.SetBattFaible(Controlleur.GetTensionBaterie());
    LED.SetBattTooHot(Controlleur.GetTemperatureBaterie());
    LED.SetObjectDetected(Controlleur.GetDistanceAvant(),Controlleur.GetDistanceArriere());
    LED.SetEndOfCourse(Controlleur.GetPositionMax(), Controlleur.GetPositionActuel());
    LED.SetCantGoSetPoint(Controlleur.GetVitesseActuel() , Controlleur.GetVitesseVoulu());
    LED.SetEmergencyStop(Controlleur.IsArretUrgence());
    LED.SetNoComms(Xbee.IsConnected());
    
    LED.UpdateLedState();
    oldTimeState = millis();
  }
  
  if(newTime > (oldTimeTransmition + 500)){
    //Xbee.TransmitionTramXbee(Controlleur, LED);
    oldTimeTransmition = millis();
  }
}
