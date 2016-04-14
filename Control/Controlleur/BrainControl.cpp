#include "BrainControl.h"

BrainControl::BrainControl(Sabertooth _SyrenDrive):
	SyrenDrive(_SyrenDrive.address(),_SyrenDrive.port()),
	CapteurDistanceAvant(TRIGGER_PIN_AVANT, ECHO_PIN_AVANT, MAX_DISTANCE),
	CapteurDistanceArriere(TRIGGER_PIN_ARRIERE, ECHO_PIN_ARRIERE, MAX_DISTANCE){

	mPositionActuel=0;
	mPositionMax=DEFAULT_POSITION_MAX;
	mVitesseActuel=0;
	mVitesseVoulu=DEFAULT_VITESSE_VOULU;
	mDistanceAvant = 0;
	mDistanceArriere = 0;
	mOutputPID = 0;
	mAcceleration=DEFAULT_ACCELERATION; 
	arretUrgence = false;
}

bool BrainControl::SetArretUrgence(bool _urg){
    arretUrgence = _urg;
    if(_urg) {digitalWrite(PIN_ARRET_URGENCE, LOW);}
    else digitalWrite(PIN_ARRET_URGENCE, HIGH);
    return arretUrgence;
}

void BrainControl::Update(){
    Encodeur.Update();
    mVitesseActuel = Encodeur.GetVitesse();
    mPositionActuel = Encodeur.GetPositionCm();
    mDistanceAvant = CapteurDistanceAvant.ping_cm();
    mDistanceArriere = CapteurDistanceArriere.ping_cm();
	
    SetVitesseVoulu(mVitesseVoulu);

    mOutputPID = PID.UpdatePid(mVitesseVoulu - mVitesseActuel,mVitesseActuel);
    if(mOutputPID>127)mOutputPID =127; //Max output qui peut etre fournit a la drive
    if(mOutputPID<-127)mOutputPID =-127;//Max output qui peut etre fournit a la drive
    
	//Gestion de l'acceleration non-utilise puisque l'on a pas un moteur assez puissant pour l'etalonner
     //Communication Serie avec la ddrive
    //if(mAcceleration == 0) {SyrenDrive.setRamping(1);}
    //else if(mAcceleration == 1) {SyrenDrive.setRamping(10);}
    //else if(mAcceleration == 2) {SyrenDrive.setRamping(25);}
    //else if(mAcceleration == 3) {SyrenDrive.setRamping(80);}
    //else if(mAcceleration == 4) {SyrenDrive.setRamping(11);}
    //else {
        SyrenDrive.setRamping(11);

    
    //Gestion des distances minimal par la position et la distance vu par les capteurs

	//Si distance en dessous de 1m -> arret selon direction voulu
    if(mDistanceArriere < MAX_POSITION_LV_1 && (mDistanceArriere != 0) )
    {
        if(mOutputPID<0) {
            mOutputPID = mVitesseVoulu =0;
        }
    }
   if(mDistanceAvant < MAX_POSITION_LV_1 && (mDistanceAvant != 0) ) 
    {
        if(mOutputPID>0) {
            mOutputPID = mVitesseVoulu =0;
        }
    }
    
	//Si position en dessous de 1m -> arret selon direction voulu
    if(mPositionActuel < MAX_POSITION_LV_1 )
    {
        if(mOutputPID<0) {
            mOutputPID = mVitesseVoulu =0;
            
        }
    }

   if(mPositionMax - MAX_POSITION_LV_1 < mPositionActuel ) 
    {
        if(mOutputPID>0) {
            mOutputPID = mVitesseVoulu =0;
        } 
    }
    
    if(arretUrgence){ mOutputPID = mVitesseVoulu =0; }
    
    
    
    
    
    
    SyrenDrive.motor(1,mOutputPID);
}

//_vitessevoulu en cm/sec
void BrainControl::SetVitesseVoulu(int _vitesseVoulu)
{
	//Une gestion des distance de capteurs et de positionement sur le cable pourrait etre realise afin de ralentir le bolide s'il
	//est pret d'un objet ou pret de la fin de sa course
    mVitesseVoulu = _vitesseVoulu;
}

bool BrainControl::SetAcceleration(int _acceleration){
    if(_acceleration == 0) mAcceleration = 0;
    else if(_acceleration == 1) mAcceleration = 1;
    else if(_acceleration == 2) mAcceleration = 2;
    else if(_acceleration == 3) mAcceleration = 3;
    else if(_acceleration == 4) mAcceleration = 4;
    else return false;
    //mAcceleration = _acceleration;
    return true;
}


