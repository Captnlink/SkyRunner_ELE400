
/**
    Project : CableCam_Chariot\n
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
        /** Default constructor */
        SrEncodeur();

        /** Update
         * @brief Mise a jour de la position et la vitesse selon les lectures de l'encodeur
         */
        void Update();

        int GetPositionCm() { return mPositionCm; }
        double GetVitesse() { return mVitesseMoy; }
        int GetDirection() { return mDirecttion; }

    private:
        Encoder EncodeurMecanique; //!< Objet "PositionCm"
        long mOldPosition;
        int mPositionCm; //!< Variable "PositionCm"
        double mVitesseMoy; //!< Variable "VitesseMoy" Vitesse Moyenne
        double mVitesseArray[SAMPLEVITESSE]; //!< Variable "VitesseArray" Vitesses pour la moyenne
        int mDirecttion;
		    double oldTime;
};

#endif // SRENCODEUR_H
