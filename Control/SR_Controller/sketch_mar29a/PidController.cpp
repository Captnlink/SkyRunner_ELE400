#include "PidController.h"

//Includes
//Include default configuration

PidController::PidController()
{
    dState;
	iState;
	//Default Configuration
	iMax = 1000;
	iMin = -1000;
	iGain = 0;
	pGain = 1;
	dGain = 0;
}


double PidController::UpdatePid(double error, double feedback){
	double pTerm, dTerm, iTerm;

	//Proportional term
	pTerm = pGain * error;

	//Intergral term
	iState += error;
	if(iState > iMax) iState = iMax;
	else if(iState < iMin) iState = iMin;
	iTerm = iGain * iState;

	//Derivate term
	dTerm = dGain * (dState - feedback);
	dState = feedback;

	//Final Sommation
	return pTerm + dTerm + iTerm;

}
