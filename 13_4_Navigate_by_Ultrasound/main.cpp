#include "mbed.h"
#include "bbcar.h"

DigitalOut led1(LED1);
PwmOut pin9(D9), pin8(D8);
DigitalInOut pin10(D10);
Ticker servo_ticker;

BBCar car(pin8, pin9, servo_ticker);

int main(void) 
{
    parallax_ping ping1(pin10);

    // go straight with some initial speed
    car.goStraight(100);
    
    while (1) {
        // (float)ping will be the return the distance to the obstacle
        // with unit cm!
        if ((float)ping1 > 10) 
            led1 = 1;
        else {
            led1 = 0;
            car.stop();
            break;
        }
        wait(.01);
    }
}