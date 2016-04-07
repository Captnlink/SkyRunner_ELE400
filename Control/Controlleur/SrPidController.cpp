#include "SrPidController.h"

//Includes
//Include default configuration

PidController::PidController()
{
    dState;
	iState;
	//Default Configuration
	iMax = 1000;
	iMin = -1000;
	iGain = INTEGRAL_GAIN;
	pGain = PROPORTIONAL_GAIN;
	dGain = DERIVATIVE_GAIN;
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
