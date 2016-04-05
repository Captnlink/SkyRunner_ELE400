/**
    @file SrCommunication.h
    @brief Contient la classe permettant la communication avec XBee

	@author Captnlink
    @author khchu1993

    @version 1.2
    @date April 4, 2016
*/

#ifndef SRCOMMUNICATION_H
#define SRCOMMUNICATION_H

#include "Arduino.h"
#include "SrConfig.h"
#include "BrainControl.h"
#include "EtatLed.h"

/**
    @class CommXBee
    @brief Permet la reception, l'emission et le traitement des informations transmise par le port serie.

    @author Captnlink
	@author khchu1993
    @version 1.3
    @date April 4, 2016
	
*/
class CommXBee
{
public:
	CommXBee();
	/** ReceiveTramXbee
	 * @brief Recois la trame de communication du Xbee
	 */
	void ReceiveTramXbee(BrainControl& _Controlleur);
	/** TransmitionTramXbee
	 * @brief Prend les informations du controlleur et les envoient au port Serie
	 * @param Controlleur: Objet de classe BrainControl
	 */
	void TransmitionTramXbee(BrainControl& Controlleur, EtatLed& LED);
	/** IsChangementConsigne
	 * @brief Verifie s'il y a changement de configuration
	 * @param Controlleur: Objet de classe BrainControl
	 */
	bool IsChangementConsigne(BrainControl& _Controlleur);
	
	/** UpdateConfiguration
	 * @brief Fais les changement de configuration
	 *@param Controlleur: Objet de classe BrainControl
	 */
	void UpdateConfiguration(BrainControl& _Controlleur);
	
	//Getters
  bool IsConnected(){return connexion;}
	bool IsArretUrgence(){return arretUrgence;}
	int GetVitesse(){return vitesse;}
	int GetAcceleration(){return acceleration;}
	int GetLongeurCable(){return longueurCable;}

private:
	String tramToSend;
	char msg[14];
	bool connexion;
	
	int manetteAdresse;
	
	// Variables pour la trame de contrôle
	int vitesse;
	bool arretUrgence;
	
	// Variables pour la trame de configuration
	int acceleration;
	int longueurCable;
	
	char checkSum;
	
	void ResetCommVariable(); 
	
	//http://projectsfromtech.blogspot.ca/2013/09/combine-2-bytes-into-int-on-arduino.html
	int BitShiftCombine( unsigned char x_high, unsigned char x_low);
	
};

#endif // SRCOMMUNICATION_H
