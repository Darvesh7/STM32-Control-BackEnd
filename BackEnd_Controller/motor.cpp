#include "mbed.h"
#include "motor.h"

Motor::Motor(PinName INA, 
    PinName INB,
    PwmOut PWM,
    PinName SEL0, 
    AnalogIn CS):

_motorINA(new DigitalOut (INA)), 
_motorINB(new DigitalOut (INB)), 
_motorPWM(new PwmOut (PWM)),
_motorSEL0(new DigitalOut (SEL0)),
_motorCS(new AnalogIn (CS))       


{
    _INA = INA;
    _INB = INB;
    _PWM = PWM;
    _SEL0 = SEL0;
    _CS = CS;

    _MState = MSTOP;
    _RPMcount = 0.0;
    _previousRPMcount = 0.0;


}  

void Motor::forward(void)
{
    if(_MState == MSTOP)
    {
        _MState = MFORWARD;

        _motorINA->write(1);
        _motorINB->write(0);   
        _motorSEL0->write(1); 
        
        pwm_value = 0.001;
        setMotorSpeed();
    }
}

void Motor::backward(void)
{
    if(_MState == MSTOP)
    {
        _MState = MBACKWARD;

        _motorINB->write(1);
        _motorINA->write(0);
        _motorSEL0->write(0);  
        
        pwm_value = 0.001;        
        setMotorSpeed();
    }

}

void Motor::stop(void)
{
    _MState = MSTOP;

    pwm_value = 0.0;
    setMotorSpeed();

    _motorINB->write(0);
    _motorINA->write(0);
    _motorSEL0->write(0); 

}

void Motor::brake(void)
{
    _MState = MBRAKE;
 
    pwm_value = 0.1;
    setMotorSpeedBrake();
    _motorINB->write(0);
    _motorINA->write(0);
    _motorSEL0->write(0); 

}

void Motor::setMotorSpeed(void)
{
    for(int pwm_i = pwm_value ; pwm_i<0.1; pwm_i++)
    {
        _motorPWM = pwm_i;
    }

}

void Motor::setMotorSpeedBrake(void)
{
    for(int pwm_i = pwm_value ; pwm_i == 0.0; pwm_i--)
    {
        _motorPWM = pwm_i;
    }
}






