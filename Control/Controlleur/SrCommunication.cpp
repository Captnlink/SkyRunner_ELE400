

#include "SrCommunication.h"

CommXBee::CommXBee(BrainControl& Controlleur){	
	for(int i = 0; i < 10; i++){msg[i] = 0;}
	connexion=0;
	
	manetteAdresse=-1;
	
	vitesse=Controlleur.GetVitesseVoulu();
	arretUrgence=Controlleur.IsArretUrgence();
	
	acceleration=Controlleur.GetAcceleration();
	longueurCable=Controlleur.GetPositionMax();
	
	ping = 0;
	
	checkSum=0;
	
	tramToSend = "";
	}


void CommXBee::TransmitionTramXbee(BrainControl& Controlleur, EtatLed& LED){
	CommXBee::ResetCommVariable();
	
//On divise les longeur par 10 afin d'envoyer en dm
long longeurMax = Controlleur.GetPositionMax()/10;
long longeurActuel = Controlleur.GetPositionActuel()/10;

  msg[0] = 'S';
  msg[1] = 'T';
  msg[2] = 'A';
  msg[3] = lowByte((int)Controlleur.GetTensionBaterie());
  msg[4] = highByte(longeurActuel);
  msg[5] = lowByte(longeurActuel);
  msg[6] = lowByte((int)Controlleur.GetVitesseVoulu());
  msg[7] = lowByte((int)Controlleur.GetVitesseActuel());
  msg[8] = lowByte(Controlleur.GetAcceleration());
  msg[9] = highByte(longeurMax);
  msg[10] = lowByte(longeurMax);
  msg[11] =  lowByte(manetteAdresse);
  msg[12] = LED.GetErrorState();
  for(int i = 0; i<13;i++){msg[13] += msg[i];}
  
  #if DEBUG
  Serial.print(" Sent Tram     ");
  #endif
   
  for(int i = 0; i<14;i++){Serial.print(msg[i]);} 
  
  
  #if DEBUG
  Serial.println("");   
  Serial.print(" Batt ");   Serial.print(" PosH ");   Serial.print(" PosL ");   Serial.print(" VitV ");   Serial.print(" VitA ");   Serial.print(" Accl ");   Serial.print(" PoMH ");   Serial.print(" PoML ");    Serial.print(" Addr ");    Serial.print(" Err  ");    Serial.println(" CSum ");
  Serial.print("  "); Serial.print((int)msg[3]);Serial.print("    ");Serial.print((int)msg[4]);Serial.print("    ");Serial.print((int)msg[5]);Serial.print("    ");Serial.print((int)msg[6]);Serial.print("    ");Serial.print((int)msg[7]);Serial.print("    ");Serial.print((int)msg[8]);Serial.print("    ");Serial.print((int)msg[9]);Serial.print("    ");Serial.print((int)msg[10]);Serial.print("    ");Serial.print((int)msg[11]);Serial.print("    ");Serial.print((int)msg[12]);Serial.print("    ");Serial.println((int)msg[12]);
  #endif
}	


void CommXBee::ReceiveTramXbee(BrainControl& _Controlleur){
	String SOF = "";
	
	//Trame de connexion verification seulement si aucun autre appareil est connecter
	if (Serial.available() && !connexion) { 
	
		CommXBee::ResetCommVariable();
	
		msg[0]=Serial.read();
		if(msg[0] != 'C') return;
		
		msg[1]=Serial.read();
		if(msg[1] != 'X') return;
		
		msg[2]=Serial.read();

		SOF += msg[0];
		SOF += msg[1];
		SOF += msg[2];
		
		if(SOF == "CXN"){
			msg[3]=Serial.read();	//Adresse
			msg[4]=Serial.read();	//CheckSum

			checkSum = msg[0] + msg[1] + msg[2] + msg[3];

      #if DEBUG
      Serial.println("");
      Serial.print(" CMD ");   Serial.print(" Addr ");   Serial.println(" CSum ");   
      Serial.print(" "); Serial.print(msg[0]);Serial.print(msg[1]);Serial.print(msg[2]);Serial.print("    ");Serial.print((int)msg[3]);Serial.print("    ");Serial.println((int)msg[4]);
      Serial.print("CheckSum : ");Serial.println(checkSum);
      #endif
      
			if(checkSum == msg[4]) {
				connexion = true;
				manetteAdresse = msg[3];
			}
			else return;
		}
   else return;
	}		
		
	//Trame lorsqu'une manette est connectee
	else if (Serial.available() && connexion) { 
	
		CommXBee::ResetCommVariable();
	
		msg[0]=Serial.read();
		if(msg[0] != 'C' && msg[0] != 'D' && msg[0] != 'P' ) return;
		
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
      
            #if DEBUG
            Serial.println("");
            Serial.print(" CMD ");                                                                                 Serial.print(" Addr "); Serial.print(" Accl ");  Serial.print(" PosH ");   Serial.print(" PosL ");   Serial.println(" CSum ");
            Serial.print(" "); Serial.print(msg[0]);Serial.print(msg[1]);Serial.print(msg[2]);Serial.print("    ");Serial.print((int)msg[3]);Serial.print("    ");Serial.println((int)msg[4]);Serial.print("  "); Serial.print((int)msg[3]);Serial.print("    ");Serial.print((int)msg[4]);Serial.print("    ");Serial.print((int)msg[5]);Serial.print("    ");Serial.print((int)msg[6]);Serial.print("    ");Serial.println((int)msg[7]);
            Serial.print("CheckSum : ");Serial.println(checkSum);
            #endif
      
			if(checkSum == msg[7] && manetteAdresse == msg[3]) {
				acceleration = msg[4];					
				longueurCable = CommXBee::BitShiftCombine(msg[5], msg[6]);
				if(IsChangementConsigne(_Controlleur)){
                    UpdateConfiguration(_Controlleur);
                    }
			}
			else return;
		}
		else if(SOF == "CNT"){
			msg[3]=Serial.read();	//Adresse
			msg[4]=Serial.read();	//Vitesse
			msg[5]=Serial.read();	//Arret Urgence
			msg[6]=Serial.read();	//CheckSum
      
          checkSum = msg[0] + msg[1] + msg[2] + msg[3] + msg[4] + msg[5];
          
          #if DEBUG
          Serial.println("");
          Serial.print(" CMD ");                                                                                 Serial.print(" Addr ");   Serial.print(" VitV ");   Serial.print(" Urg ");   Serial.println(" CSum ");
          Serial.print(" "); Serial.print(msg[0]);Serial.print(msg[1]);Serial.print(msg[2]);Serial.print("    ");Serial.print((int)msg[3]);Serial.print("    ");Serial.println((int)msg[4]);Serial.print("  "); Serial.print((int)msg[5]);Serial.print("    ");Serial.println((int)msg[6]);
          Serial.print("CheckSum : ");Serial.println(checkSum);
          #endif

			if(checkSum == msg[6] && manetteAdresse == msg[3]) {
				vitesse = msg[4];
				arretUrgence = msg[5];
				_Controlleur.SetArretUrgence(arretUrgence);
				if(IsChangementConsigne(_Controlleur)){
                    UpdateConfiguration(_Controlleur);
                    }
			}
			else return;
		}		
		else if(SOF == "DCX"){
			msg[3]=Serial.read(); //Byte pour adresse
			msg[4]=Serial.read(); //Byte pour CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3];
			if(checkSum == msg[4]) {
				if(manetteAdresse == msg[3]){
					connexion = false;
					manetteAdresse = -1;
				    if(IsChangementConsigne(_Controlleur)){
                        UpdateConfiguration(_Controlleur);
                        }
				}
			}
			else return;
		}
		else if(SOF == "PNG"){
			msg[3]=Serial.read(); //Byte pour adresse
			msg[4]=Serial.read(); //Byte pour CheckSum
			
			checkSum = msg[0] + msg[1] + msg[2] + msg[3];
			if(checkSum == msg[4]) {
				if(manetteAdresse == msg[3]){
					ping = 0;
				}
			}
			else return;
		}
		
    else return;
	  }
else return;
}

void CommXBee::ResetCommVariable(){
	for(int i = 0; i < 14; i++){msg[i] = 0;}
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
	if(_Controlleur.GetPositionMax() != longueurCable*10) 	return true;
	if(_Controlleur.GetAcceleration() != acceleration) 	return true;
	return false;
}

void CommXBee::UpdateConfiguration(BrainControl& _Controlleur){
	if(_Controlleur.GetVitesseVoulu() != vitesse) _Controlleur.SetVitesseVoulu(vitesse);
	if(_Controlleur.GetPositionMax() != longueurCable*10) _Controlleur.SetPositionMax(longueurCable*10);
	if(_Controlleur.GetAcceleration() != acceleration) _Controlleur.SetAcceleration(acceleration);
}
