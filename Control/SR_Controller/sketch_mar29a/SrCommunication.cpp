

#include "SrCommunication.h"

CommXBee::CommXBee(){	
	for(int i = 0; i < 10; i++){msg[i] = 0;}
	connexion=0;
	
	manetteAdresse=-1;
	
	vitesse=0;
	arretUrgence=0;
	
	acceleration=0;
	longueurCable=0;
	
	checkSum=0;
	
	tramToSend = "";
	}

void CommXBee::TransmitionTramXbee(BrainControl& Controlleur){
	tramToSend = ""; //Reset Tram
	tramToSend += "STA";
	tramToSend += lowByte((int)Controlleur.GetTensionBaterie());
	tramToSend += highByte(Controlleur.GetPositionActuel());
	tramToSend += lowByte(Controlleur.GetPositionActuel());
	tramToSend += lowByte(Controlleur.GetVitesseVoulu());
	tramToSend += lowByte(Controlleur.GetVitesseActuel());
	tramToSend += lowByte(Controlleur.GetAcceleration());
	tramToSend += highByte(Controlleur.GetPositionMax());
	tramToSend += lowByte(Controlleur.GetPositionMax());
	tramToSend += lowByte(manetteAdresse);
	tramToSend += B10010;
	tramToSend += tramToSend.length();
	Serial.print(tramToSend);
}	
	
void CommXBee::ReceiveTramXbee(){
	
	String SOF = "";
	
	//Trame de connexion
	if (Serial.available() && !connexion) { 
	
		CommXBee::ResetCommVariable();
	
		msg[0]=Serial.read();
		if(msg[0] != 'C') return;
		
		msg[1]=Serial.read();
		if(msg[0] != 'N') return;
		
		msg[2]=Serial.read();

		SOF += msg[0];
		SOF += msg[1];
		SOF += msg[2];
		
		if(SOF == "CNF"){
			msg[3]=Serial.read();	//Adresse
			msg[4]=Serial.read();	//CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3];
			if(checkSum == msg[4]) {
				connexion = true;
				manetteAdresse = msg[3];
			}
			return;
		}
	}		
		
	//Trame lorsque manette connecter
	if (Serial.available() && connexion) { 
	
		CommXBee::ResetCommVariable();
	
		msg[0]=Serial.read();
		if(msg[0] != 'C' && msg[0] != 'D') return;
		
		msg[1]=Serial.read();
		if(msg[1] != 'N' && msg[1] != 'C') return;
		
		msg[2]=Serial.read();

		SOF += msg[0];
		SOF += msg[1];
		SOF += msg[2];
		
		if(SOF == "CNF"){
			msg[3]=Serial.read(); //Byte pour adresse
			msg[4]=Serial.read(); //Byte pour acceleration
			msg[5]=Serial.read(); //Byte pour Longeur HighByte
			msg[6]=Serial.read(); //Byte pour Longeur LowByte
			msg[7]=Serial.read(); //Byte pour CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3] + msg[4] + msg[5] + msg[6];
			if(checkSum == msg[7] && manetteAdresse == msg[3]) {
				acceleration = msg[4];					
				longueurCable = CommXBee::BitShiftCombine(msg[5], msg[6]);
			}
			return;
		}
		if(SOF == "CNT"){
			msg[3]=Serial.read();	//Adresse
			msg[4]=Serial.read();	//Vitesse
			msg[5]=Serial.read();	//Arret Urgence
			msg[6]=Serial.read();	//CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3] + msg[4] + msg[5];
			if(checkSum == msg[6] && manetteAdresse == msg[3]) {
				vitesse = msg[4];
				arretUrgence = msg[5];
			}
			return;
		}		
		if(SOF == "DCX"){
			msg[3]=Serial.read(); //Byte pour adresse
			msg[4]=Serial.read(); //Byte pour CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3];
			if(checkSum == msg[4]) {
				if(manetteAdresse == msg[3])
					connexion = false;
					manetteAdresse = -1;
			}
			return;
		}		

	}
}

void CommXBee::ResetCommVariable(){
	for(int i = 0; i < 10; i++){msg[i] = 0;}
}

int CommXBee::BitShiftCombine( unsigned char x_high, unsigned char x_low)
{
  int combined;
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in rightmost 8 bits
  return combined;
}

bool CommXBee::IsChangementConsigne(BrainControl& _Controlleur){
	
	if(_Controlleur.GetVitesseVoulu() != vitesse) 		return true;
	if(_Controlleur.GetPositionMax() != longueurCable) 	return true;
	if(_Controlleur.GetAcceleration() != acceleration) 	return true;
	return false;
}

void CommXBee::UpdateConfiguration(BrainControl& _Controlleur){
	if(_Controlleur.GetVitesseVoulu() != vitesse) _Controlleur.SetVitesseVoulu(vitesse);
	if(_Controlleur.GetPositionMax() != longueurCable) _Controlleur.SetPositionMax(longueurCable);
	if(_Controlleur.GetAcceleration() != acceleration) _Controlleur.SetAcceleration(acceleration);
}
