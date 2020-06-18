#include "mbed.h"


typedef enum
{
    MFORWARD,
    MBACKWARD,
    MSTOP,
    MBRAKE
} motorState_t;

class Motor
{
     public:
    // CONSTRUCTOR
    // User-defined pin selection.
    Motor(PinName INA, 
    PinName INB,
    PwmOut PWM,
    PinName SEL0, 
    AnalogIn CS);

    void init(void);

    void forward(void);
    void backward(void);
    void stop(void);
    void brake(void);

    void setMotorSpeed(void);
    void setMotorSpeedBrake(void);
    void setMotorSpeed(int);
    void getMotorSpeed(void);
    
    int getCurrent(void);

    float pwm_value = 0.0;
    double RPM = 0.0;
    float pwm_i = 0.0;

    motorState_t _MState;



    private:

    PinName _INA;
    PinName _INB;
    PwmOut _PWM;
    PinName _SEL0;
    AnalogIn _CS;

    DigitalOut* _motorINA;
    DigitalOut* _motorINB;
    PwmOut* _motorPWM;
    DigitalOut* _motorSEL0;
    AnalogIn* _motorCS;

    float _RPMcount;
    float _previousRPMcount;
 

    bool _faultly;



};
