/*
  Xbee1
  The circuit: 
  * RX = pin 2 (connecter à TX de XBee)
  * TX = pin 3 (connecter à RX de XBee)
*/

#include <SoftwareSerial.h>


SoftwareSerial xbee(2, 3); // RX, TX
char msg[10] = {0,0,0,0,0,0,0,0,0,0};
int NbBit = 0;
int Connexion = 0;
int ManetteAdresse = 0;
// Variables pour la trame de contrôle
int Vitesse = 0;
int ArretUrgence = 0;
// Variables pour la trame de configuration
int Acceleration = 0;
int Deceleration = 0;
int LongueurCable[2] = {0,0};
int Receiver = 0;



void setup()  {
   Serial.begin(9600);
}

void ReceiveUpdate() {
// Si Xbee a recu quelque

// Trame de demande de connexion: SOF = CXN
// msg[4] = tableau 1*4
// msg[0] = SOF[0]
// msg[1] = SOF[1]
// msg[2] = SOF[2]
// msg[3] = Adresse de la manette
// msg[4] = Checksum
if (Connexion == 0){
Serial.println("Not connecte");
}
else{
Serial.println("Connecte");  
}
Serial.println(NbBit);


if (Serial.available() > 0 && Connexion == 0) { 
  msg[NbBit]=Serial.read();
  Receiver = 1;
  Serial.println(NbBit);
  Serial.println(msg[NbBit]);
  // Trame de demande de connexion 
  if (NbBit==0 && Receiver == 1){
    if (msg[0]== 'C'){                                                             // si la première lettre = C
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
  }
  if (NbBit ==1 && Receiver == 1){
    if (msg[1]== 'X'){                                                             // si la première lettre = C
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
  }
  if (NbBit ==2 && Receiver == 1){
    if (msg[2]== 'N'){                                                             // si la première lettre = C
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
  }
  if (NbBit==3 && Receiver == 1){
    NbBit++;
    Receiver = 0;
  }
  if (NbBit==4 && Receiver == 1){
    if (msg[4] == '4'){                                                            // si le contrôle a reçu toute la trame
      Connexion = 1;                                                               // si oui, connecter
      ManetteAdresse = msg[3];                                                     // prendre en note l'adresse de la manette connectée
      Serial.println("Connexion On");
    }
  NbBit=0;                                                                         // recommencer peu importe si on a reçu toute la trame au complête
  Receiver = 0;
  }   
}

if (Serial.available() > 0 && Connexion == 1 ) {
  msg[NbBit]=Serial.read();
  Receiver = 1;
  Serial.println(NbBit);
  Serial.println(msg[NbBit]);

  if (NbBit==0 && Receiver == 1){
    if (msg[0]== 'C' || msg[0]== 'D'){                                             // si la première lettre = C ou D
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
    Serial.println(NbBit);
  }
  if (NbBit==1 && Receiver == 1){
    if (msg[0]== 'C' && msg[1]== 'N'){                                             // si les deux premières lettres = C et N
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else if (msg[0]== 'D' && msg[1]== 'C'){                                        // si les deux premières lettres = D et C               
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
    Serial.println(NbBit);
  }
  if (NbBit==2 && Receiver == 1){
    if (msg[0]== 'C' && msg[1]== 'N' && msg[2]== 'T'){                             // si les trois premières lettres = C, N et T (Trame de contrôle)              
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else if (msg[0]== 'C' && msg[1]== 'N' && msg[2]== 'F'){                        // si les trois premières lettres = C, N et F (Trame de configuration)                   
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else if (msg[0]== 'D' && msg[1]== 'C' && msg[2]== 'X'){                        // si les trois premières lettres = D, C et X (Trame de demande de déconnexion)                              
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
    Serial.println(NbBit);
  }
  if (NbBit==3 && Receiver == 1){                                                  // si la trame est envoyé par la manette qu'on a connectée
    if (ManetteAdresse == msg[3]){  
      NbBit++;                                                                     // si oui, continuer
      Receiver = 0;
      Serial.println(NbBit);
    }
    else{                                                                          // si non, recommencer
      NbBit=0;
      Receiver = 0;
    }
  }
  if (NbBit==4 && Receiver == 1){                                                                   
    if (msg[0]== 'D' && msg[1]== 'C' && msg[2]== 'X'){                             // Pour la trame de demande de déconnexion
      if (msg[4] == '4'){                                                          // si le contrôle a reçu toute la trame
        Connexion = 0;                                                             // si oui, déconnecter
        Serial.println("Connexion off");
      }
    Receiver = 0;
    NbBit=0;                                                                       // recommencer peu importe si on a reçu toute la trame au complête
    }
    else{                                                                          // si la trame reçue n'est pas la trame de demande de déconnexion, continuer
      NbBit++;
      Receiver = 0;
    }
  }
  if (NbBit==5 && Receiver == 1){
    NbBit++;
    Receiver = 0;
  }
  if (NbBit==6 && Receiver == 1){                                                                   
    if (msg[0]== 'C' && msg[1]== 'N' && msg[2]== 'T'){                             // Pour la trame de contrôle
      if (msg[6] == '6'){                                                          // si le contrôle a reçu toute la trame
        Vitesse = msg[4];                                                          // si oui, prendre en note la vitesse demandée
        ArretUrgence = msg[5];                                                     // prendre en note si l'arrêt d'urgence est demandé
        Serial.println("Controle");
      }
    Receiver = 0;
    NbBit = 0;                                                                     // recommencer peu importe si on a reçu toute la trame au complête
    }
    else{                                                                          // si la trame reçue n'est pas la trame de demande de déconnexion, continuer
      NbBit++;
      Receiver = 0;
    }
  }
  if (NbBit==7 && Receiver == 1){                                                                   
    if (msg[0]== 'C' && msg[1]== 'N' && msg[2]== 'F' && msg[7] == '7'){            // Pour la trame de configuration, si le contrôle a reçu toute la trame
      Acceleration = msg[4];                                                       // si oui, prendre en note l'accélération requise
      LongueurCable[0] = msg[5];                                                   // prendre en note la longueur du câble utilisé
      LongueurCable[1] = msg[6];      
      Serial.println("Configuration");
    }  
    NbBit = 0;                                                                   // recommencer peu importe si on a reçu toute la trame au complête
    Receiver = 0;
  }
  
}
delay(1000);
}

void loop(){
  ReceiveUpdate();
}
