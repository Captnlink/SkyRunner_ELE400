#include "SrEtatLed.h"

EtatLed::EtatLed(){
	flashLedState = 0; //�tat de la LED (Allum� ou �teinte)
  errorState = 0;
  oldTime = 0;
	SetGood(true);
}



/*
	SetGood(); 			//Constinuly GREEN
	SetBattFaible();	//Flash Red Red Red Red
	SetBattTooHot();	//Flash Red Yel Red Yel
	SetObjectDetected(); //Flash Red Red Yel Yel
	SetEndOfCourse();	//Flash Yel Yel Yel Yel
	SetCantGoSetPoint();//Flash Grn Grn Grn Grn
	SetEmergencyStop();	//Constinuly RED
	SetNoComms(); 		//Constinuly YELLOW
*/

#define MAX_LED_UPDATE 11

bool EtatLed::UpdateLedState(/*State of Controler*/){

    	const char color_CR[MAX_LED_UPDATE] = {RED,RED,RED,RED,RED,RED,RED,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                                       //Urgence
    	const char color_CY[MAX_LED_UPDATE] = {YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                  //No Comms
    	const char color_CG[MAX_LED_UPDATE] = {GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                         //Good
    	const char color_FR[MAX_LED_UPDATE] = {RED,NO_LIGHT,RED,NO_LIGHT,RED,NO_LIGHT,RED,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                        //Low Batt
    	const char color_FY[MAX_LED_UPDATE] = {YELLOW,NO_LIGHT,YELLOW,NO_LIGHT,YELLOW,NO_LIGHT,YELLOW,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};             //End of Course
    	const char color_FG[MAX_LED_UPDATE] = {GREEN,NO_LIGHT,GREEN,NO_LIGHT,GREEN,NO_LIGHT,GREEN,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                //Cant go Set Speed
    	const char color_FRY[MAX_LED_UPDATE] = {RED,NO_LIGHT,YELLOW,NO_LIGHT,RED,NO_LIGHT,YELLOW,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};                 //Hot Batterie
    	const char color_FRRYY[MAX_LED_UPDATE] = {RED,NO_LIGHT,RED,NO_LIGHT,YELLOW,NO_LIGHT,YELLOW,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};               //Object detected
    	const char color_CN[MAX_LED_UPDATE] = {NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT,NO_LIGHT};    //End of Update
		
		switch(errorState)
	    {
    	case 0 : 
    	//Const green
            if((STATE_GOOD & controllerState)){
                Serial.println("Good");
                ChangeLedColor(color_CG[flashLedState]);
                flashLedState++;
                
            	if(flashLedState >= MAX_LED_UPDATE-1) {
            		errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
            	}
            	break;
            }
            else errorState++;
    	case 1:
        	//Flash Red
        	if((STATE_LOWBATT & controllerState)){
        	    Serial.println("Batteire faible");
        	    if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==1) {
        			flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
        		}
        	    
        	    ChangeLedColor(color_FR[flashLedState]);
        	    flashLedState++;
        	    
        		if(flashLedState >= MAX_LED_UPDATE-1) {
        			errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
        		}
        		break;
        	}
        	else errorState++;
		case 2:
            //Flash Red Yellow
            if((STATE_HOTBATT & controllerState)){
    		    Serial.println("Batterie chaude");
    			if(flashLedState >= MAX_LED_UPDATE-1 && errorState == 2) {
    				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    		    
    		    ChangeLedColor(color_FRY[flashLedState]);
    		    flashLedState++;
    		    
    			if(flashLedState >= MAX_LED_UPDATE-1) {
    				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    			break;
    		}
            else errorState++;
		case 3:
            //Flash RED RED YELLOW YELLOW
            if((STATE_OBJDETECT & controllerState)){
                Serial.println("Objet detecter");
                if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==3) {
                    flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
                }
                
                ChangeLedColor(color_FRRYY[flashLedState]);
                flashLedState++;
                
                if(flashLedState >= MAX_LED_UPDATE-1) {
                    errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
                }
                break;
            }
            else errorState++;
        case 4:
            //Flash Yellow
            if((STATE_ENDCOURSE & controllerState)){
    		    Serial.println("End Course");
    			if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==4) {
    				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    		    
    		    ChangeLedColor(color_FY[flashLedState]);
    		    flashLedState++;
    		    
    			if(flashLedState >= MAX_LED_UPDATE-1) {
    				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    			break;
    		}
            else errorState++;   
            
        case 5:    
            //Flash Green
            if((STATE_NOSETPOINT & controllerState)){
		    Serial.println("Pas la vitesse voulu");
			if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==5) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FG[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState >= MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
			break;
		}
            else errorState++;
        
        case 6:
            //Const Red
    		if((STATE_EMERGENCY & controllerState)){
    		    Serial.println("Urgence");
    			if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==6) {
    				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    		    
    		    ChangeLedColor(color_CR[flashLedState]);
    		    flashLedState++;
    		    
    			if(flashLedState >= MAX_LED_UPDATE-1) {
    				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    			break;
    		}
    		else errorState++;
	    case 7:
    	    //const yellow
    		if(errorState== 7 && (STATE_NOCOMMS & controllerState)){
    		    Serial.println("Pas de Comms");
    			if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==7) {
    				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    		    
    		    ChangeLedColor(color_CY[flashLedState]);
    		    flashLedState++;
    		    
    			if(flashLedState >= MAX_LED_UPDATE-1) {
    				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    			break;
    		}
    		else errorState++;
    	case 8:
    	    //Const No light
    		if(errorState== 8){
    		    Serial.println("End of Update");
    			if(flashLedState >= MAX_LED_UPDATE-1 && errorState ==8) {
    				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    		    
    		    ChangeLedColor(color_CN[flashLedState]);
    		    flashLedState++;
    		    
    			if(flashLedState >= (MAX_LED_UPDATE-1)/2) {
    				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
    			}
    			break;
    		}
    		else errorState++;
		default:
    		
    		if(errorState>8){
    		    errorState=0;
    		    flashLedState =0;
    		}
    		break;
	}
    		
		
	/*	
		//Constantament Green
		if(errorState== 0 && (STATE_GOOD & controllerState)){
		    Serial.println("Good");
		    ChangeLedColor(color_CG[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}

		}
		else errorState++;
		
		//Flash Red
		if(errorState== 1 && (STATE_LOWBATT & controllerState)){
		    Serial.println("Batteire faible");
		    if(flashLedState == MAX_LED_UPDATE-1 && errorState ==1) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FR[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//Flash Red Yellow
		if(errorState== 2 && (STATE_HOTBATT & controllerState)){
		    Serial.println("Batterie chaude");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState == 2) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FRY[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//Flash RED RED YELLOW YELLOW
		if(errorState== 3 && (STATE_OBJDETECT & controllerState)){
		    Serial.println("Objet detecter");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==3) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FRRYY[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;

        //Flash Yellow
		if(errorState== 4 && (STATE_ENDCOURSE & controllerState)){
		    Serial.println("End Course");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==4) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FY[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//Flash Green
		if(errorState== 5 && (STATE_NOSETPOINT & controllerState)){
		    Serial.println("Pas la vitesse voulu");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==5) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_FG[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//Const Red
		if(errorState== 6 && (STATE_EMERGENCY & controllerState)){
		    Serial.println("Urgence");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==6) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_CR[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//const yellow
		if(errorState== 7 && (STATE_NOCOMMS & controllerState)){
		    Serial.println("Pas de Comms");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==7) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_CY[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == MAX_LED_UPDATE-1) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		else errorState++;
		
		//Const No light
		if(errorState== 8){
		    Serial.println("End of Update");
			if(flashLedState == MAX_LED_UPDATE-1 && errorState ==8) {
				flashLedState=0; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		    
		    ChangeLedColor(color_CN[flashLedState]);
		    flashLedState++;
		    
			if(flashLedState == (MAX_LED_UPDATE-1)/2) {
				errorState++; // modifie etape _erreur pour v�rifier la prochaine erreur d�tect�
			}
		}
		if(errorState>8)errorState=0;*/
	
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
	default:
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
