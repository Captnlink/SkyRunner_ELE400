#include "SrEncodeur.h"

SrEncodeur::SrEncodeur():EncodeurMecanique(2, 3)
{
    mOldPosition = -999;
    mVitesseArray[10] = {0};
    mPositionCm = 0;
    mVitesseMoy = 0;
    mDirecttion = 0;
	oldTime =0;
}

void SrEncodeur::Update(){

    long newPosition = EncodeurMecanique.read();

    //Calcul de la direction
    if(newPosition > mOldPosition)       mDirecttion = DIRECTION_AVANT;
    else if(newPosition < mOldPosition)  mDirecttion = DIRECTION_ARRIERE;
    else    mDirecttion = DIRECTION_NULL;

    //Calcul de position actuel en cm
    mPositionCm = 3.75 * newPosition * (2 * 3.1415 * RAYONCM / 360); /*3.75 est la convertion de 96 pulses a 360 degrees*/

    //Calcul de vitesse
    long newTime = millis();
    long vitesseAngulaire = ((3.75 * newPosition - 3.75 * mOldPosition)/(newTime-oldTime)*1000/*Miliseconde a seconde*/); //Degrees par seconde

    mOldPosition = newPosition;
    oldTime = newTime;

    //Calcul vitesse moyenne
    mVitesseArray[SAMPLEVITESSE-1] = vitesseAngulaire * RAYONCM; // Cm/sec
    mVitesseMoy = 0;
    for(int i = 0; i < SAMPLEVITESSE; i++){
        mVitesseArray[i] = mVitesseArray[i+1];
        mVitesseMoy += mVitesseArray[i];
    }
    mVitesseMoy /= SAMPLEVITESSE;
}
