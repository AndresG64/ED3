#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Pines usados (puedes cambiarlos si quieres)
#define PIN_CS   17     // Chip Select
#define PIN_SCK  18     // SPI0 SCK
#define PIN_MISO 16     // SPI0 RX (SO del MAX6675)

float read_max6675() {
    uint8_t data[2];

    // Activar chip (CS en LOW)
    gpio_put(PIN_CS, 0);
    sleep_us(10);

    // Leer 2 bytes (16 bits)
    spi_read_blocking(spi0, 0x00, data, 2);

    // Desactivar chip
    gpio_put(PIN_CS, 1);

    // Armar los 16 bits
    uint16_t raw = (data[0] << 8) | data[1];

    // Si bit 2 está en 1 → termopar desconectado
    if (raw & 0x04) {
        return -1000.0; // Indicador de error
    }

    // Bits 14:3 contienen el valor
    raw >>= 3;
    float temp = raw * 0.25f;

    return temp;
}

int main() {
    stdio_init_all();

    // Inicialización SPI0
    spi_init(spi0, 1000 * 1000); // 1 MHz
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);

    // CS como GPIO
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);  // Inactivo (HIGH)

    // Mensaje inicial
    printf("MAX6675 listo\n");

    while (1) {
        float t = read_max6675();

        if (t < -500) {
            printf("Error: termopar desconectado\n");
        } else {
            printf("Temperatura = %.2f °C\n", t);
        }

        sleep_ms(1000);
    }
}