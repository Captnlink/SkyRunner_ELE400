/*! 
 *	Controle de chariot pour camera sur cable
 *
 * Presentation
 *
 * L'equipe est SkyRunner. Nous somme un groupe d'etudiant de l'ecole de technologie superieur.
 * Dans le but de notre cours ELE400 - Methodologie de design, nous devons develloper une technologie
 * pour un client. Notre mandat, offert par Tribor Design, est de faire un chariot de camera sur cable
 * repondant a certain critere de securite en plus de faire de la recherche sur diffente technologie pouvant accomplir
 * les besoins du client./n/n
 *
 * L'equipe est compose de 8 etudiants en genie electrique./n
 * Gestionnaire d'equipe - Samuel Geoffroy-heroux AKA CaptnLink/n
 * Coordonateur des communication externe et ingenieur chef du module controle - Antoine Champoux AKA antoine0670/n
 * Coordonateur des achats - David Prairie-Bourgoult AKA purepp666/n
 * Chef ingenieur du module interface - Alexi Demers AKA aledemers/n
 * Chef ingenieur du module communication - Danny Arseneau AKA dannyarseneau/n
 * Chef ingenieur du montage mechanique et electrique - Marc-Daniel Paul/n
 * Ingenieur - Ka Hey Chu AKA khchu1993/n
 * Ingenieur - Wantel Simon AKA Wsmon/n
 */
 
/**
 * @author 	CaptnLink
 * @email  	samuel.geoffroy.92@gmail.com
 * 
 * @author 	Wsmon
 * @email  
 * 
 * @author 	khchu
 * @email  
 * 
 * @author 	Antoine Champoux
 * @email  
 * @ide    	Arduino IDE 1.6.7
 * @ide 	Create.Arduino.cc/ide 
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
CommXBee Xbee(Controlleur);

//Creation objet Leds
EtatLed LED;

//Variable pour timer de mise a jour
long oldTimeTransmition = 0;
long oldTimeState = 0;

//Il serait peut etre interressant d'utilise un Arduino Mega afin de laisse libre le port de communication serie connecter avec le port USB
//afin de pouvoir programmer le Arduino meme si le shield est monter dessus. 

//L'encodeur doit etre sur une entree avec des interrupts (pins 2 et 3 sur le UNO)

Le port de reception (RX) serie pour la drive est inutile puisque la drive n'envoie aucune information ni confirmation.

void setup() {
  Serial.begin(9600);   //Communication Serie Hardware - XBee
  mySerial.begin(9600); //Communication Serie Software - Drive
  pinMode(PIN_ARRET_URGENCE, OUTPUT); 
}

void loop() {

  //Update du controlleur
  /*
	La classe controlleur fait la gestion de tout les capteurs. De plus, elle gere les erreurs de positionement et de detection d'obstacle.
	Après avoir fait la gestion de ses processus de securite, on met a jour le PID du controlleur et on controle la drive.
  */
    Controlleur.Update();
	
  //Gestion de la reception de communication issus d'un interface
  Xbee.ReceiveTramXbee(Controlleur);
  
  //Gestion des erreurs 
  long newTime = millis();
  if(newTime > (oldTimeState + DELAY_ETAT_LED)){
  
    LED.SetBattFaible(Controlleur.GetTensionBaterie());
    LED.SetBattTooHot(Controlleur.GetTemperatureBaterie());
    LED.SetObjectDetected(Controlleur.GetDistanceAvant(),Controlleur.GetDistanceArriere());
    LED.SetEndOfCourse(Controlleur.GetPositionActuel(), Controlleur.GetPositionMax());
    LED.SetCantGoSetPoint(Controlleur.GetVitesseActuel() , Controlleur.GetVitesseVoulu());
    LED.SetEmergencyStop(Controlleur.IsArretUrgence());
    LED.SetNoComms(Xbee.IsConnected());

    //Changement d'etat de la LED selon les erreurs
    LED.UpdateLedState();
    oldTimeState = millis();
  }
  
  //Gestion de la transmittion des donnees
  //On envoie l'objet de la LED et du controlleur afin d'envoyer l'etat actuel des objets 
  if(newTime > (oldTimeTransmition + DELAY_SEND_TRAM)){
    Xbee.TransmitionTramXbee(Controlleur, LED);
    oldTimeTransmition = millis();
  }
   
}
