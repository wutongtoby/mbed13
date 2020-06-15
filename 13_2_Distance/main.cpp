#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin8(D8), pin9(D9);
DigitalIn pin3(D3);

BBCar car(pin8, pin9, servo_ticker);

int main(void) 
{
    parallax_encoder encoder0(pin3, encoder_ticker);
    // set the initial step to 0
    encoder0.reset();

    car.goStraight(100);
    // detect if we have arrived at 30cm every 50ms
    while(encoder0.get_cm() < 30) 
        wait_ms(50);
    // if we jump out from the loop then we have gone through 30cm, so we
    // can stop the car!
    car.stop();
}
