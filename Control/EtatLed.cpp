EtatLed::EtatLed(){
	ledActualState = 0; //�tat de la LED (Allum� ou �teinte)
	controllerState = 0; //�tat du controlleur
}

bool EtatLed:UpdateLedState(/*State of Controler*/){
	return false;
}