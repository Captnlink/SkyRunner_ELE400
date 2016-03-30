/**
    Project : CableCam_Chariot\n
    @file Controller.h
    @brief PID_Controller class inside

    @author Samuel Geoffroy AKA Captnlink
    @version 1.1
    @date March 20, 2016

*/

#ifndef PidController_H_
#define PidController_H_

/**
    @class PidController Controller.h
    @brief PID Controller

    @author Captnlink
    @version 1.1
    @date March 20, 2016

    This class contain a PID controller with the respective gain for proportional, integral and derivative
*/
class PidController
{
private:
    double  dState; //Last position
    double  iState; //Integrator state
    double  iMax,iMin; //MAx and min allowable integrator state

    //PID Gain
    double  iGain; // Integral Gain
    double  pGain; // Proportional Gain
    double  dGain; // Derivative Gain

public:
    PidController();

    /**
    @fn UpdatePid
    @brief This fonction refresh the output of the controller
    @param error     : setpoint - feedback
    @param feedback  : feedback from machinery
    @return output   : % of output

    The controller use proportional, integral and derivative operation to drive an output

    */
    double UpdatePid(double error, double feedback);

    //Setters
    void setpGain(double p){pGain = p;}
    void setiGain(double i){iGain = i;}
    void setdGain(double d){dGain = d;}

    //Getters
    double getpGain(){return pGain;}
    double getiGain(){return iGain;}
    double getdGain(){return dGain;}

};

#endif
