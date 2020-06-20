#include "mbed.h"
#include "motor.h"
#include "QEI.h"




Motor::Motor (PinName INA, 
    PinName INB,
    PinName PWM,
    PinName SEL0, 
    PinName CS,
    QEI* QEI_Handle):

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


    _QEI_Handle =QEI_Handle;

    _CurrentRpmCount = 0;
    _LastRpmCount = 0;  
    _Pulses = 0;
    _CummulativePulses = 0;

    _RPMcount = 0.0;
    _previousRPMcount = 0.0;


    float pwm_i = 0.0;  
    float pwm_d = 0.0;

    _motorINA->write(0);
    _motorINB->write(0);
    _motorSEL0->write(0);

    _motorPWM->write(0);
    _motorCS = 0;

}  

void Motor::forward(void)
{
    if(_MState == MSTOP)
    {
        _MState = MFORWARD;

        _motorINA->write(1);
        _motorINB->write(0);   
        _motorSEL0->write(1); 
 
        setMotorSpeed();
      
    }
}

void Motor::backward(void) 
{
  if (_MState == MSTOP) 
  {
    _MState = MBACKWARD;


      _motorINA->write(0);
      _motorINB->write(1);
      _motorSEL0->write(1);

      setMotorSpeed();
  }
}

void Motor::stop(void)
{
    _MState = MSTOP;

    _motorINB->write(0);
    _motorINA->write(0);
    _motorSEL0->write(0); 

}

void Motor::brakeForward(void)
{
    _MState = MBRAKE;
 
    setMotorSpeedBrakeForward();


}

void Motor::brakeBackward(void)
{
    _MState = MBRAKE;
 
    setMotorSpeedBrakeBackward();


}

void Motor::setMotorSpeed(void)
{
     for(float pwm_i = 0.0 ; pwm_i <= 1.0; pwm_i += 0.005)
    {
        _motorPWM->write(pwm_i);
        printf("pwm increment %.2f\n",pwm_i);
       
    }
}

void Motor::setMotorSpeedBrakeForward(void)
{

    pwm_i = 0;
   
    _motorINA->write(1);
    _motorINB->write(0);
    _motorSEL0->write(1); 

    for(float pwm_d = 1.0 ; pwm_d >= 0.0; pwm_d-= 0.02)
    {
        _motorPWM->write(pwm_d);
        printf("pwm decrement %.2f\n",pwm_d);
    }
        
}

void Motor::setMotorSpeedBrakeBackward(void)
{

    pwm_i = 0;
   
    _motorINA->write(0);
    _motorINB->write(1);
    _motorSEL0->write(1); 

    for(float pwm_d = 1.0 ; pwm_d >= 0.0; pwm_d-= 0.02)
    {
        _motorPWM->write(pwm_d);
        printf("pwm decrement %.2f\n",pwm_d);
    }
        
}



void Motor::getRPM(void)
{
    _RPMcount = _QEI_Handle->getRevolutions();  

   
}

void Motor::getPulses(void)
{
    _Pulses = _QEI_Handle->getPulses();

}

void Motor::getCummulativePulses(void)
{
    _CummulativePulses = _Pulses + _Pulses; 
    
}

void Motor::resetEncoder(void)
{
    _QEI_Handle->reset();

}




