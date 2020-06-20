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
    PinName PWM,
    PinName SEL0, 
    PinName CS);

    void init(void);

    void forward(void);
    void backward(void);
    void stop(void);
    void brakeForward(void);
    void brakeBackward(void);

    void setMotorSpeed(void);
    void setMotorSpeedBrakeForward(void);
    void setMotorSpeedBrakeBackward(void);
    void setMotorSpeed(int);
    void getMotorSpeed(void);
    
    int getCurrent(void);

    void getRPM(void);

    float pwm_value; 
    float pwm_value_brake;
    float pwm_i; //pwm increment
    float pwm_d; //pwm decrement

    uint8_t CurrentRpmCount;
    uint8_t LastRpmCount;

    motorState_t _MState;



    private:

    PinName _INA;
    PinName _INB;
    PinName _PWM;
    PinName _SEL0;
    PinName _CS;

    DigitalOut* _motorINA;
    DigitalOut* _motorINB;
    PwmOut* _motorPWM;
    DigitalOut* _motorSEL0;
    AnalogIn* _motorCS;

    float _RPMcount;
    float _previousRPMcount;
 

    bool _faultly;



};
