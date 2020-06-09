#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin9(D9), pin8(D8);
Serial xbee(D12, D11);
BBCar car(pin8, pin9, servo_ticker);

// just wait for rpc call from the xbee!
int main(void) 
{
    // for D8
    double pwm_table0[] = {-50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50};
    double speed_table0[] = {-25.440, -20.974, -15.551, -10.288, -4.785, 0, 0.799, 5.742, 11.484, 16.189, 20.177};
    
    // for D9
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-16.747, -16.349, -12.392, -12.521, -6.539, 0, 5.184, 11.404, 14.193, 16.269, 16.747};

    // first and fourth argument : length of table
    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);
    
    char buf[256], outbuf[256];
    
    while (1) {
        for (int i = 0; ; i++) {
            buf[i] = xbee.getc();
            if (buf[i] == '\n') 
                break;
        }

        RPC::call(buf, outbuf);
        xbee.printf("%s\r\n", outbuf);

    }
}