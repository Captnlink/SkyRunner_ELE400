#include "SrEncodeur.h"

SrEncodeur::SrEncodeur():EncodeurMecanique(ENCODEUR_PIN_A, ENCODEUR_PIN_B)
{
    mOldPosition = -999;
    mVitesseArray[SAMPLEVITESSE] = {0};
    mPositionCm = 0;
    mOldPositionCm=0;
    mVitesseMoy = 0;
    mDirecttion = 0;
	oldTime =0;
	newTime = 0;
}

void SrEncodeur::Update(){
    long deltaTime;
    long newPosition = EncodeurMecanique.read();
    

    //Calcul de la direction
    if(newPosition > mOldPosition)       mDirecttion = DIRECTION_AVANT;
    else if(newPosition < mOldPosition)  mDirecttion = DIRECTION_ARRIERE;
    else    mDirecttion = DIRECTION_NULL;

    //Calcul de position actuel en cm
    mPositionCm = newPosition/96 * (2 * 3.1415 * RAYONCM)*100; /*3.75 est la convertion de 96 pulses a 360 degrees*/

    newTime = millis();
    
	//Ajuste la vitesse si on a une variation de position d'un 1/8 de tour ou 50 millisecondes de timer
    if(newPosition>mOldPosition+12 || newPosition<mOldPosition-12 || (newTime-oldTime) > 50){
    
    deltaTime = newTime-oldTime ;
    oldTime = newTime ;
    
	//Calcul de vitesse
    mVitesseMoy = (double) ( (( (double)(newPosition-mOldPosition) /96.0)*2.0 * 3.1415 * RAYONCM) / (((double)deltaTime) /1000.0) ); //Degrees par seconde
    mVitesseMoy = mVitesseMoy*100/3.35;

    mOldPosition = newPosition;
    }
   
}
