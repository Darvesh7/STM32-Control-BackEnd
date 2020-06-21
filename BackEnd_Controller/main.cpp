#include "mbed.h"
#include "motor.h"
#include "QEI.h"
#define ENC_PPR 2338

QEI* encoder;
Motor* motor;

void setup()
{
encoder = new QEI(PA_1, PA_2, NC,ENC_PPR);
motor = new Motor(PB_5,PB_4,PB_3,PA_10,PA_4, encoder);

}


int main()
{
    void setup();

    motor->forward();
    wait_ms(2000);
    motor->brakeForward();
    wait_ms(2000);
    motor->stop();
    wait_ms(2000);
    motor->backward();
    wait_ms(2000);
    motor->brakeBackward();
    wait_ms(5000);



    while(1)
    {
     
       //printf("%d\n",encoder->getPulses());
          
    }

}







