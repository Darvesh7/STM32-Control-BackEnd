#include "mbed.h"
 
DigitalOut myled(LED2);
 
int main() {
    while(1) {
        myled = 1;
        ThisThread::sleep_for(2000);
        myled = 0;
        ThisThread::sleep_for(2000);
        
    }
}
 