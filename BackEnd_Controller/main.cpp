#include "mbed.h"
#include "motor.h"



Motor motor(PB_5,PB_4,PB_3,PA_10,PA_4);

int main()
{


    motor.forward();
    wait_ms(2000);
    motor.brakeForward();
    wait_ms(2000);
    motor.stop();
    wait_ms(2000);
    motor.backward();
    wait_ms(2000);
    motor.brakeBackward();
    wait_ms(5000);


    while(1)
    {
    
    }


}







