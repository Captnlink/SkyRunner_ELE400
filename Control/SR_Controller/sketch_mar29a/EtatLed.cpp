#include "EtatLed.h"

EtatLed::EtatLed(){
	flashLedState = 0; //�tat de la LED (Allum� ou �teinte)
  errorState = 0;
  oldTime = 0;
	SetGood(true);
}


#define BATTERIE_LOW 12
#define TEMP_BATT_TOO_HOT 40

//D�lai du cycle pour regarder l'�tat des led et aussi d�lai de  clignotement
#define DELAY_ETAT_LED 250

// Statut des led pour les switch case pour fonction etat-led
#define GREEN 1
#define RED 2
#define YELLOW 3
#define NO_LIGHT 4

// Pin pour les leds sur le Arduino
#define PIN_LD_GREEN 7
#define PIN_LD_RED 8

#define STATE_GOOD 0
#define STATE_LOWBATT 1
#define STATE_HOTBATT 2
#define STATE_OBJDETECT 4
#define STATE_ENDCOURSE 8
#define STATE_NOSETPOINT 16
#define STATE_EMERGENCY 32
#define STATE_NOCOMMS 64

/*
	SetGood(); 			//Constinuly GREEN
	SetBattFaible();	//Flash Red Red Red Red
	SetBattTooHot();	//Flash Red Red Yel Yel
	SetObjectDetected();//Flash Red Yel Red Yel
	SetEndOfCourse();	//Flash Yel Yel Yel Yel
	SetCantGoSetPoint();//Flash Grn Grn Grn Grn
	SetEmergencyStop();	//Constinuly RED
	SetNoComms(); 		//Constinuly YELLOW
*/
bool EtatLed::UpdateLedState(/*State of Controler*/){
	int newTime = millis();
	if(newTime>oldTime+DELAY_ETAT_LED){
		
		if(errorState== 0 && (STATE_GOOD & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
				flashLedState=0; // remet � 0 le cycle de clignotement
			}
			else {
				ChangeLedColor(GREEN);
				flashLedState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		
		if(errorState== 1 && (STATE_LOWBATT & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; 
				flashLedState=0; 
			}
			else if(flashLedState%2 == 0 ) {
				ChangeLedColor(RED);
				flashLedState++;
			}
			else if(flashLedState%2 == 1 ) {
				ChangeLedColor(NO_LIGHT);
				flashLedState++; 
			}
		}
		
		if(errorState== 2 && (STATE_HOTBATT & controllerState)){
			switch(flashLedState){
				case 0:
					ChangeLedColor(RED);
					flashLedState++;
					break;
				case 2:
					ChangeLedColor(RED);
					flashLedState++;
					break;
				case 4:
					ChangeLedColor(YELLOW);
					flashLedState++;
					break;
				case 6:
					ChangeLedColor(YELLOW);
					flashLedState++;
					break;
				case 7:
					ChangeLedColor(NO_LIGHT);
					errorState++; 
					flashLedState=0; 
					break;
				default:
					ChangeLedColor(NO_LIGHT);
					flashLedState++; 
					break;
			}
		}
		
		if(errorState== 3 && (STATE_OBJDETECT & controllerState)){
			switch(flashLedState){
				case 0:
					ChangeLedColor(YELLOW);
					flashLedState++;
					break;
				case 2:
					ChangeLedColor(YELLOW);
					flashLedState++;
					break;
				case 4:
					ChangeLedColor(RED);
					flashLedState++;
					break;
				case 6:
					ChangeLedColor(RED);
					flashLedState++;
					break;
				case 7:
					ChangeLedColor(NO_LIGHT);
					errorState++; 
					flashLedState=0; 
					break;
				default:
					ChangeLedColor(NO_LIGHT);
					flashLedState++; 
					break;
			}
		}

		if(errorState== 4 && (STATE_ENDCOURSE & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; 
				flashLedState=0; 
			}
			else if(flashLedState%2 == 0 ) {
				ChangeLedColor(YELLOW);
				flashLedState++;
			}
			else if(flashLedState%2 == 1 ) {
				ChangeLedColor(NO_LIGHT);
				flashLedState++; 
			}
		}
		if(errorState== 5 && (STATE_NOSETPOINT & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; 
				flashLedState=0; 
			}
			else if(flashLedState%2 == 0 ) {
				ChangeLedColor(GREEN);
				flashLedState++;
			}
			else if(flashLedState%2 == 1 ) {
				ChangeLedColor(NO_LIGHT);
				flashLedState++; 
			}
		}
		if(errorState== 6 && (STATE_EMERGENCY & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
				flashLedState=0; // remet � 0 le cycle de clignotement
			}
			else {
				ChangeLedColor(RED);
				flashLedState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		if(errorState== 7 && (STATE_NOCOMMS & controllerState)){
			if(flashLedState == 7) {
				ChangeLedColor(NO_LIGHT);
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
				flashLedState=0; // remet � 0 le cycle de clignotement
			}
			else {
				ChangeLedColor(YELLOW);
				flashLedState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		if(errorState== 8){
			ChangeLedColor(NO_LIGHT);
			if(flashLedState == 7) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
				flashLedState=0; // remet � 0 le cycle de clignotement
			}
			else {
				flashLedState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
	}
	return false;
}

void EtatLed::ChangeLedColor(int color)
{
	switch(color)
	{
		//Allumer seulement led rouge
	case RED : 
		digitalWrite(PIN_LD_RED,HIGH);
		digitalWrite(PIN_LD_GREEN,LOW);
		break;
		//Allumer seulement lumi�re verte
	case GREEN: 
		digitalWrite(PIN_LD_RED,LOW);
		digitalWrite(PIN_LD_GREEN,HIGH);
		break;

		//Allumer led rouge et vert pour lumi�re jaune
	case YELLOW: 
		digitalWrite(PIN_LD_RED,HIGH);
		digitalWrite(PIN_LD_GREEN,HIGH);
		break;
		//�teindre toutes les lumi�res
	case NO_LIGHT: 
		digitalWrite(PIN_LD_RED,LOW);
		digitalWrite(PIN_LD_GREEN,LOW);
		break;
	}
}
//Setters
bool EtatLed::SetGood(bool state){
	if(state)
	{
		controllerState = controllerState & STATE_GOOD;
		return true;
	}
	else
	{
		return false;
	}
}

bool EtatLed::SetBattFaible(double tensionBatterie){
	if(tensionBatterie<BATTERIE_LOW)
	{
		controllerState = controllerState | STATE_LOWBATT;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_LOWBATT;
		return false;
	}
}

bool EtatLed::SetBattTooHot(double tempBatterie){
	if(tempBatterie<TEMP_BATT_TOO_HOT)
	{
		controllerState = controllerState | STATE_HOTBATT;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_HOTBATT;
		return false;
	}
}

bool EtatLed::SetObjectDetected(int distanceObjetDetecteAvant, int distanceObjetDetecteArriere){
	if(distanceObjetDetecteAvant != -1 || distanceObjetDetecteArriere != -1)
	{
		controllerState = controllerState | STATE_OBJDETECT;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_OBJDETECT;
		return false;
	}

}

bool EtatLed::SetEndOfCourse(int positionActuel, int PositionMax){
	if(PositionMax - MAX_POSITION_LV_5 < positionActuel || MAX_POSITION_LV_5 > positionActuel)
	{
		controllerState = controllerState | STATE_ENDCOURSE;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_ENDCOURSE;
		return false;
	}
}

bool EtatLed::SetCantGoSetPoint(int vitesseActuel, int vitesseVoulu){
	if(vitesseVoulu > vitesseActuel)
	{
		controllerState = controllerState | STATE_NOSETPOINT;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_NOSETPOINT;
		return false;
	}
}

bool EtatLed::SetEmergencyStop(bool state){
	if(state)
	{
		controllerState = controllerState | STATE_EMERGENCY;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_EMERGENCY;
		return false;
	}
}

bool EtatLed::SetNoComms(bool state){
	if(state)
	{
		controllerState = controllerState | STATE_NOCOMMS;
		return true;
	}
	else
	{
		controllerState = controllerState & ~STATE_NOCOMMS;
		return false;
	}
}
