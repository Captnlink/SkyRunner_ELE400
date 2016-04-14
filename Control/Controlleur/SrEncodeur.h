/**

    @file SrEncodeur.h
    @brief Recupere la vitesse et distance lineaire

    @author Captnlink

    @version 1.0
    @date March 20, 2016

    @warning Il y a un delai(2000) (2s) dans le constructeur().
*/

#ifndef SRENCODEUR_H
#define SRENCODEUR_H

#include "Arduino.h"
//#define ENCODER_OPTIMIZE_INTERRUPTS
#include "Encoder.h"
#include "SrConfig.h"

#define DIRECTION_ARRIERE   -1
#define DIRECTION_AVANT     1
#define DIRECTION_NULL    0

class SrEncodeur
{
    public:
        SrEncodeur();
        /** Update
         * @brief Mise a jour de la position et la vitesse selon les lectures de l'encodeur
         */
        void Update();

		//Getters
        int GetPositionCm() { return mPositionCm; }
        double GetVitesse() { return mVitesseMoy; }
        int GetDirection() { return mDirecttion; }

    private:
        Encoder EncodeurMecanique;
        long mOldPosition;
        double mPositionCm; 
        double mOldPositionCm;
        double mVitesseMoy; 
        double mVitesseArray[SAMPLEVITESSE]; 
        int mDirecttion;
		double oldTime;
		double newTime;
};

#endif // SRENCODEUR_H
