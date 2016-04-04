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


#include "BrainControl.h"
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
CommXBee Xbee;

long oldTime = 0;

void setup() {
  Controlleur.SetPositionMax(1000); //Longeur du cable 1000 cm

  Serial.begin(9600);   //Communication Serie Hardware - XBee
  mySerial.begin(9600); //Communication Serie Software - Drive
}

void loop() {
  //Update du controlleur
  Controlleur.Update();
  
  Xbee.ReceiveTramXbee();
  if(Xbee.IsChangementConsigne(Controlleur)){
    Xbee.UpdateConfiguration(Controlleur);
    }

  long newTime = millis();
  if(newTime > (oldTime + 20)){
    Xbee.TransmitionTramXbee(Controlleur);
    oldTime = millis();
  }
}

