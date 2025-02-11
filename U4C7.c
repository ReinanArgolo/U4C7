#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "inc/include.h"



int main()
{
    stdio_init_all();

    init_pwm();

    sleep_ms(1000);
    
    sleep_ms(1000);
    
    servo_positions_test();

    
    while (true) {
        servo_sweep();
    }
}
