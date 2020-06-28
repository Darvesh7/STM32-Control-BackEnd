#include "mbed.h"
#include "motor.h"
#include "QEI.h"
#include "eeprom.h"
#include "PinDetect.h"
#include "loos_states.h"

#define ENC_PPR 2338
#define EEPROM_ADDR 0x01 
#define MODE_BUTTON PC_8 


PinDetect ModeButton (USER_BUTTON);
 
DigitalOut myled(LED2);

PinDetect Flush_button(PA_1);  
PinDetect ResetButton(PA_8); 
PinDetect ForwardButton(PC_6);  
PinDetect BackwardButton(PC_5); 


QEI* encoder;
Motor* motor;
EEPROM* ep;

typedef enum 
{ 
    MA_Forward, 
    MA_Backward,
    MA_Brake,
    MA_Stop
} MA_t;

MA_t gMotorAction = MA_Stop;

sysState_struct_t sysState_struct;

T_MenuState MenuState = ME_INITIALISING;

Semaphore motorSema(1);

Thread t1;
Thread t2;

EventFlags stateChanged;

void setup_flush_button(void); 
void setup_reset_button(void); 
void setup_forward_button(void); 
void setup_backward_button(void); 
void setup_Mode_button(void); 
  


void SystemStates_thread(void const *name);
void motorDrive_thread(void const *name); 



void setup(void)
{
    sysState_struct.sysMode = S_RUN;
    encoder = new QEI (PA_7, PA_6, NC,ENC_PPR);
    motor = new Motor (PB_5,PB_4,PB_3,PA_10,PA_4);
    ep = new EEPROM (PB_9, PB_8, EEPROM_ADDR, EEPROM::T24C512);

    setup_reset_button();
    setup_flush_button();
    setup_forward_button();
    setup_backward_button();
    setup_Mode_button();

    t1.start(callback(motorDrive_thread, (void *)"MotorDriveThread"));
    t2.start(callback(SystemStates_thread, (void *)"SystemStateThread"));
 
}

int main()
{
    setup();
}

/********************************************************/
// Internal Functions
/********************************************************/

void reset_eeprom(void) 
{ 
   
}

void manual_forward_asserted(void) 
{
    if(motor->_MState == MSTOP)
    {
        gMotorAction = MA_Backward;
        motorSema.release();
    }  
}

void manual_backward_asserted(void) 
{
    if(motor->_MState == MSTOP)
    {
        gMotorAction = MA_Backward;
        motorSema.release();
    }

}

void manual_deasserted(void)
{
    if(motor->_MState == MFORWARD || MBACKWARD)
    {
        gMotorAction = MA_Brake;
        motorSema.release();
    }

}

void start_flush(void) 
{
    if(motor->_MState == MSTOP)
    {
        gMotorAction = MA_Forward;
        motorSema.release();
    }
}

void end_flush(void) 
{
    if(motor->_MState == MFORWARD)
    {
        gMotorAction = MA_Brake;
        motorSema.release();
    }
}

void mode_button_asserted (void)
{
    stateChanged.set(0x01);
}


void setup_flush_button(void) 
{
    Flush_button.mode(PullUp);
    Flush_button.attach_asserted(&start_flush);
    Flush_button.attach_deasserted(&end_flush);
    Flush_button.setSamplesTillAssert(10); // debounces 10 sample by
    Flush_button.setAssertValue(0);        // state of the pin
    Flush_button.setSampleFrequency();     // Defaults to 20ms.
}

void setup_reset_button(void) 
{

    ResetButton.mode(PullUp);
    ResetButton.attach_asserted(&reset_eeprom);
    ResetButton.setSamplesTillAssert(10); // debounces 10 sample by 20ms = 200 ms
    ResetButton.setAssertValue(0);        // state of the pin from Low to High
    ResetButton.setSampleFrequency();     // Defaults to 20ms.
}


void setup_forward_button(void)
{

    ForwardButton.mode(PullUp);
    ForwardButton.attach_asserted(&manual_forward_asserted);
    ForwardButton.attach_deasserted(&manual_deasserted);
    ForwardButton.setSamplesTillAssert(10); // debounces 10 sample by 20ms = 200 ms
    ForwardButton.setAssertValue(0);        // state of the pin from Low to High
    ForwardButton.setSampleFrequency();     // Defaults to 20ms.

}

void setup_backward_button(void)
{

    BackwardButton.mode(PullUp);
    BackwardButton.attach_asserted(&manual_backward_asserted);
    BackwardButton.attach_deasserted(&manual_deasserted);
    BackwardButton.setSamplesTillAssert(10); // debounces 10 sample by 20ms = 200 ms
    BackwardButton.setAssertValue(0);        // state of the pin from Low to High
    BackwardButton.setSampleFrequency();     // Defaults to 20ms.

}

void setup_Mode_button(void)
{

    ModeButton.mode(PullUp);
    ModeButton.attach_asserted(&mode_button_asserted);
    ModeButton.setSamplesTillAssert(10); // debounces 10 sample by 20ms = 200 ms
    ModeButton.setAssertValue(0);        // state of the pin from Low to High
    ModeButton.setSampleFrequency();     // Defaults to 20ms.
}

void MenuAction(void)
{
    switch(MenuState)
    {
        case ME_INITIALISING:
        break;

        case ME_RUN:

        break;

        case ME_SERVICE:
        
        break;

        case ME_JAM:
        break;

        case ME_SETUP:
        break;

        default:
            break;

    }
    
}

void SystemStates_thread(void const *name) 
{
  while (true) 
  {
    stateChanged.wait_any(0x01);  
    switch (sysState_struct.sysMode) 
    {
    case S_RUN:
      printf("RUN_STATE\n");
      sysState_struct.sysMode = S_SER;

      break;
    case S_SER:
      printf("SERVICE_STATE\n");
      sysState_struct.sysMode = S_SET;
      break;
    case S_SET:
      printf("SETUP_STATE\n");
      sysState_struct.sysMode = S_RUN;

      break;
    default:
      printf("Error: Undefined Mode\n");
      break;
    }
  }
}


void motorDrive_thread(void const *name) 
{
    while (true) 
    {
        motorSema.acquire();
        switch(gMotorAction)
        {
            case MA_Forward:
                motor->forward();
            break;
            case MA_Backward:
                motor->backward();
            break;
            case MA_Brake:
                motor->brake();
            break;
            case MA_Stop:
                motor->stop();
            break;
        }
    }
}








