#include <stdio.h>
#include "pico/stdlib.h"

/**<Include modulos */
#include "lcd_module.h"
#include "adc_temp.h"
#include "adc_setpoint.h"
#include "pid.h"


int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
