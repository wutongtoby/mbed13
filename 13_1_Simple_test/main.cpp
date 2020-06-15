#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D9);
BBCar car(pin8, pin9, servo_ticker);

int main(void) 
{
    while (1) {
        car.goStraight(100);
        wait(1);
        car.stop();
        wait(1);
    }

}
