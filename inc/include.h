#include <stdio.h>
#include "hardware/pwm.h"
#include "pico/stdlib.h"

const uint SERVO_PIN = 12;
const uint16_t PERIOD = 20000; // Período de 20ms para ~50Hz
const float DIVIDER_PWM = 125.0f; // Atualizado para que 1 count ≈ 1µs
const uint16_t STEPS = 100;

void init_pwm() {
    uint slice;
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Define a função GPIO para PWM
    slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o slice do PWM
    pwm_set_clkdiv(slice, DIVIDER_PWM);
    pwm_set_wrap(slice, PERIOD);
    pwm_set_enabled(slice, true); // Enable the PWM output

}

// Atualizado: usa o canal PWM correto para definir o ciclo ativo em µs
void servo_set_duty(uint16_t duty_us) {
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);
    pwm_set_chan_level(slice, channel, duty_us);
}

// Rotina para definir a posição do servo e aguardar um tempo (ms)
void servo_position(uint16_t duty_us, uint32_t delay_ms) {
    servo_set_duty(duty_us);
    sleep_ms(delay_ms);
}

// Varre o servo suavemente entre 500µs (~0°) e 2400µs (~180°)
// Incremento/decremento de 5µs com atraso de 10ms para movimento suave
void servo_sweep() {
    const uint16_t duty_min = 500;
    const uint16_t duty_max = 2400;
    const uint16_t step = 5;

    uint16_t duty = duty_min;
    // Varre para cima
    while (duty <= duty_max) {
        servo_set_duty(duty);
        sleep_ms(10);
        duty += step;
    }
    // Varre para baixo
    duty = duty_max;
    while (duty >= duty_min) {
        servo_set_duty(duty);
        sleep_ms(10);
        // Evita underflow
        if (duty < step) break;
        duty -= step;
    }
}

// Rotina para posições fixas com atraso de 5 segundos cada
void servo_positions_test() {
    // Posição ~180°: duty = 2400µs
    servo_position(2400, 5000);
    printf("Posição 180°\n");
    // Posição ~90°: duty = 1470µs
    servo_position(1470, 5000);
    printf("Posição 90°\n");
    // Posição ~0°: duty = 500µs
    servo_position(500, 5000);
    printf("Posição 0°\n");
}