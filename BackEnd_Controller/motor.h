#include "mbed.h"
#include "QEI.h"


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
    PinName CS,
    QEI * QEI_Handle);

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

    void resetEncoder(void);
    void getRPM(void);
    void getPulses(void);
    void getCummulativePulses(void);

    float pwm_value; 
    float pwm_value_brake;
    float pwm_i; //pwm increment
    float pwm_d; //pwm decrement


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

    QEI * _QEI_Handle;

    float _RPMcount;
    float _previousRPMcount;

    uint8_t _CurrentRpmCount;
    uint8_t _LastRpmCount;

    uint32_t _Pulses;
    uint32_t _CummulativePulses;
 

    bool _faultly;



};
