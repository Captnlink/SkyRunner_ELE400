/**
    Project : CableCam_Chariot\n
    @file
    @brief 

	@author Chu
    @author Captnlink

    @version 1.1
    @date 

*/

#ifndef SRCOMMUNICATION_H
#define SRCOMMUNICATION_H

#include "Arduino.h"
#include "SrConfig.h"
#include "BrainControl.h"


class CommXBee
{
public:
	  CommXBee();
        /** ReceiveTramXbee
         * @brief Recois la trame de communication du Xbee
         */
		void ReceiveTramXbee();
		void TransmitionTramXbee(BrainControl& Controlleur);
		/** IsChangementConsigne
         * @brief Verifie s'il y a changement de configuration
         */
		bool IsChangementConsigne(BrainControl& _Controlleur);
		
		/** UpdateConfiguration
         * @brief Fais les changement de configuration
         */
		void UpdateConfiguration(BrainControl& _Controlleur);
		
		//Getters
		bool IsArretUrgence(){return arretUrgence;}
		int GetVitesse(){return vitesse;}
		int GetAcceleration(){return acceleration;}
		int GetLongeurCable(){return longueurCable;}

private:
		String tramToSend;
		char msg[10];
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
		int BitShiftCombine( unsigned char x_high, unsigned char x_low);
	
};

#endif // SRCOMMUNICATION_H
