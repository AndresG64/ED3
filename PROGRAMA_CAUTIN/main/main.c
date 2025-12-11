#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

/**<Include modulos */
#include "lcd_module.h"
#include "adc_temp.h"
#include "adc_setpoint.h"
#include "pid.h"

 /**<
#define RS 16
#define RW 17
#define E 18
#define D4 22
#define D5 21
#define D6 20
#define D7 19 
*/ 
#define PWM 22

ADCTempConfig adc_temp_sensor;
PIDController pid_controller;

uint16_t temperature = 0;
double duty = 0.0;

bool ban_pid = false;
bool ban_lcd = false;
bool ban_adc = false;

bool pid_callback(struct repeating_timer *t) {
    ban_pid = true;
    return true;
}

bool lcd_callback(struct repeating_timer *t) {
    ban_lcd = true;
    return true;
}
bool adc_callback(struct repeating_timer *t) {
    ban_adc = true;
    return true;
}


int main()
{
    stdio_init_all();

    adc_temp_init(&adc_temp_sensor, 26, 0); /**<Pin ADC 26, canal 0 */
    adc_temp_data_set(&adc_temp_sensor);

    PIDController_init(&pid_controller, 0.025, 0.001, 0.0); /**<Kp, Ki, Kd */

    /**<PWM */
    gpio_set_function(PWM, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM);
    uint channel   = pwm_gpio_to_channel(PWM);
    pwm_set_clkdiv(slice_num, 125.0f);  /**<Divisor de reloj para ajustar la frecuencia */
    pwm_set_wrap(slice_num, 999); /**<Frecuencia PWM */
    // Inicializar duty (por ejemplo 50%)
    pwm_set_chan_level(slice_num, channel, 0);
    pwm_set_enabled(slice_num, true);

    /**<Interrupciones */   
    struct repeating_timer timer_pid;
    add_repeating_timer_ms(50, pid_callback, NULL, &timer_pid);  // 50 ms

    struct repeating_timer timer_lcd;
    add_repeating_timer_ms(1000, lcd_callback, NULL, &timer_lcd);  // 1s

    struct repeating_timer t_adc;
    add_repeating_timer_ms(100, adc_callback, NULL, &t_adc);   // ADC: 100 ms

    while (true) {

        if (ban_adc){
            ban_adc = false;
            temperature = adc_temp_read_temperature(&adc_temp_sensor);
        }

        if (ban_pid) {
            ban_pid = false;
            duty = PIDController_compute(&pid_controller, 100.0, (double)temperature, 0.050); // dt = 1ms
            if (duty > 1.0) {
                duty = 1.0;
            } else if (duty < 0.0) {
                duty = 0.0;
            }
            pwm_set_chan_level(slice_num, channel, (uint16_t)((1-duty) * 999));
        }

        if (ban_lcd){
            ban_lcd = false;
            printf("Temperature: %d C\n", temperature);
            printf("Duty Cycle: %.2f %%\n", duty * 100.0);
        }
    }
}
