/**
 * @file lcd.c
 * @brief Implementación de la librería para controlar una pantalla LCD en modo 4 bits
 * @details Contiene el desarrollo de las funciones para manejar la pantalla LCD
 * @author Andres David Quiñonez Rueda
 * @date 2025-10-9
 */

#include "lcd.h"

void lcd_gpio_init(int pin){
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void set_pulse(LCD *lcd){
    lcd->E.value = 1;
    gpio_put(lcd->E.pin, lcd->E.value); /**<Habilitar la escritura */ 
    sleep_us(60);        /**<Mantener el pulso por al menos 1 microsegundo*/
    lcd->E.value = 0;
    gpio_put(lcd->E.pin, lcd->E.value); /**< Deshabilitar la escritura */
}

void LCD_update_gpio(LCD *lcd){
    gpio_put(lcd->RS.pin, lcd->RS.value);
    gpio_put(lcd->RW.pin, lcd->RW.value);
    gpio_put(lcd->DataPins.D4.pin, lcd->DataPins.D4.value);
    gpio_put(lcd->DataPins.D5.pin, lcd->DataPins.D5.value);
    gpio_put(lcd->DataPins.D6.pin, lcd->DataPins.D6.value);
    gpio_put(lcd->DataPins.D7.pin, lcd->DataPins.D7.value);
}

void LCD_init(LCD *lcd, int RS, int RW, int E,
              int D4, int D5, int D6, int D7)
{
    lcd->RS.pin = RS;
    lcd_gpio_init(RS);
    lcd->RW.pin = RW;
    lcd_gpio_init(RW);
    lcd->E.pin = E;
    lcd_gpio_init(E);
    lcd->DataPins.D4.pin = D4;
    lcd_gpio_init(D4);
    lcd->DataPins.D5.pin = D5;
    lcd_gpio_init(D5);
    lcd->DataPins.D6.pin = D6;
    lcd_gpio_init(D6);
    lcd->DataPins.D7.pin = D7;
    lcd_gpio_init(D7);
}


void LCD_sendCommand(LCD *lcd, uint8_t command, int delay, int is_data)
{
    lcd->RS.value = is_data ? 1 : 0;
    lcd->RW.value = 0;

    /**<delay es el tiempo en estabilización de los comando en el gpio*/
    lcd->DataPins.D7.value = (command >> 7) & 0b1; /**< Extraer bit DB7*/
    lcd->DataPins.D6.value = (command >> 6) & 0b1; /**< Extraer bit DB6*/
    lcd->DataPins.D5.value = (command >> 5) & 0b1; /**< Extraer bit DB5*/
    lcd->DataPins.D4.value = (command >> 4) & 0b1; /**< Extraer bit DB4*/

    LCD_update_gpio(lcd); /**< Actualizar los pines GPIO con los valores establecidos*/
    set_pulse(lcd); /**< Enviar pulso para los primeros 4 bits*/
    sleep_us(delay);

    lcd->DataPins.D7.value = (command >> 3) & 0b1; /**< Extraer bit DB3*/
    lcd->DataPins.D6.value = (command >> 2) & 0b1; /**< Extraer bit DB2*/
    lcd->DataPins.D5.value = (command >> 1) & 0b1; /**< Extraer bit DB1*/
    lcd->DataPins.D4.value = command & 0b1; /**< Extraer bit DB0*/

    LCD_update_gpio(lcd); /**<  Actualizar los pines GPIO con los valores establecidos*/
    set_pulse(lcd); /**<  Enviar pulso para los últimos 4 bits*/
    sleep_us(delay);
}

void LCD_clear_display(LCD *lcd){
    LCD_sendCommand(lcd, 0b00000001, 2000, 0); /**< Comando para limpiar la pantalla*/
}

void LCD_return_home(LCD *lcd){
    LCD_sendCommand(lcd, 0b00000010, 2000, 0); /**< Comando para regresar al inicio*/
}

void LCD_entry_mode_set(LCD *lcd, int ID, int S){
    uint8_t command = 0b00000100 | (ID << 1) | S;
    LCD_sendCommand(lcd, command, 100, 0);  /**< Comando para configurar el modo de entrada*/
}

void LCD_display_control(LCD *lcd, int D, int C, int B){
    uint8_t command = 0b00001000 | (D<<2) | (C<<1) | B;
    LCD_sendCommand(lcd, command, 100, 0); /**< Comando para controlar la pantalla*/ 
}

void LCD_cursor_display_shift(LCD *lcd, int SC, int RL){
    uint8_t command = 0b00010000 | (SC<<3) | (RL<<2);
    LCD_sendCommand(lcd, command, 100, 0); /**< Comando para desplazar el cursor o la pantalla*/
}

void LCD_function_set(LCD *lcd, int DL, int N, int F){
    uint8_t command = 0b00100000 | (DL<<4) | (N<<3) | (F<<2);
    LCD_sendCommand(lcd, command, 100, 0); /**< Comando para configurar la función del LCD*/
}

void LCD_set_ddram_address(LCD *lcd, int address){
    uint8_t command = 0b10000000 | (address & 0b1111111);
    LCD_sendCommand(lcd, command, 100, 0); /**< Comando para establecer la dirección DDRAM*/
}

void  LCD_write_data(LCD *lcd, char data){
    uint8_t command = 0b00000000 | (data & 0b11111111);
    LCD_sendCommand(lcd, command, 100, 1); /**< Comando para escribir datos en el LCD*/
}

void LCD_inicialization_sequence(LCD *lcd){
    LCD_sendCommand(lcd, 0b00110011, 4500, 0); 
    sleep_us(120);
    LCD_sendCommand(lcd, 0b00110010, 150, 0);
    LCD_function_set(lcd, 0, 1, 0);     /**< Modo de 4 bits, 2 líneas, fuente 5x8*/
    LCD_display_control(lcd, 0, 0, 0);  /**< Pantalla y cursor apagados*/
    LCD_entry_mode_set(lcd, 1, 0);      /**< Desplazamiento a la derecha, sin desplazamiento de pantalla*/
    LCD_clear_display(lcd);             /**< Limpiar pantalla*/
    sleep_ms(2);
    LCD_display_control(lcd, 1, 0, 0);  /**< Pantalla encendida, cursor apagado, sin parpadeo*/
}


void LCD_print(LCD *lcd, char word[2][17]){
    LCD_clear_display(lcd);
    LCD_return_home(lcd);
    LCD_set_ddram_address(lcd, 0b00000000); /**< Dirección inicial de la primera línea*/
    int i;
    for(i = 0; i < 16 && word[0][i] != '\0'; i++){
        LCD_write_data(lcd, word[0][i]);
    }
    LCD_set_ddram_address(lcd, 0b01000000); /**< Dirección inicial de la segunda línea*/
    for(i = 0; i < 16 && word[1][i] != '\0'; i++){
        LCD_write_data(lcd, word[1][i]);
    }
}