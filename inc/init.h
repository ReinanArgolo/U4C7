#include "hardware/pwm.h"
#include "pico/stdlib.h"

const uint SERVO_PIN = 22;
const uint16_t PERIOD = 2000;
const float DIVIDER_PWM = 16.0f;
const uint16_t STEPS = 100;

void init_pwm() {
    uint slice;
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // alterar porta
    slice = pwm_gpio_to_slice_num(SERVO_PIN); // alterar porta
    pwm_set_clkdiv(slice, DIVIDER_PWM);
    pwm_set_wrap(slice, PERIOD);
}