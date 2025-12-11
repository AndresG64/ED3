/**
 * @file lcd_module.h
 * @author Andres David Quiñonez Rueda
 * @brief Declaraciones de la librería para controlar una pantalla LCD en modo 4 bits
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#define LCD_H
#ifdef LCD_H

#include "pico/stdlib.h"
#include <stdint.h>
/**
 * @brief Estructura para definir un pin del LCD
 * 
 */
typedef struct{
    int pin;
    int value;
}Pin;

/**
 * @brief Estructura principal para manejar el LCD
 * 
 */
typedef struct{
    Pin RS;
    Pin RW;
    Pin E;
    struct LCD_DataPins
    {
        Pin D4;
        Pin D5;
        Pin D6;
        Pin D7;
    } DataPins;
}LCD;

/**
 * @brief Inicializa un pin GPIO como salida que se usará en el LCD
 * 
 * @param pin 
 */
void lcd_gpio_init(int pin);

/**
 * @brief Pulso en el enable para habilitar la escritura en el LCD
 * 
 * @param lcd 
 */
void set_pulse(LCD *lcd);

/**
 * @brief Función que actualiza los pines GPIO con los valores almacenados en la estructura LCD
 * 
 * @param lcd 
 */
void LCD_update_gpio(LCD *lcd);

/** 
 * @brief Función que inicializa los pines del LCD
 * 
 * @param lcd Estructura LCD que contiene los pines
 * @param RS Seleccionar registro (0: comando, 1: dato)
 * @param RW Leer/Escribir (0: escribir, 1: leer)
 * @param E Enable (Habilitar escritura)
 * @param D4 
 * @param D5 
 * @param D6 
 * @param D7 
 */
void LCD_init(LCD *lcd, int RS, int RW, int E,
              int D4, int D5, int D6, int D7);

/**
 * @brief Enviar comandos al LCD de 8 bits, se guarda en value el valor de cada pin
 * 
 * @param lcd 
 * @param command 
 * @param delay 
 * @param is_data 
 */
void LCD_sendCommand(LCD *lcd, uint8_t command, int delay, int is_data);



//----------Funciones para controlar el LCD----------//

/**
 * @brief Función para limpiar la pantalla
 * 
 * @param lcd 
 */
void LCD_clear_display(LCD *lcd);

/**
 * @brief Función para regresar el cursor al inicio
 * 
 * @param lcd 
 */
void LCD_return_home(LCD *lcd);

/**
 * @brief Función para definir el comportamiento del cursor
 * 
 * @param lcd 
 * @param ID Movimiento del cursor (1: derecha, 0: izquierda)
 * @param S desplazamiento de la pantalla (1: sí, 0: no)
 */
void LCD_entry_mode_set(LCD *lcd, int ID, int S);

/**
 * @brief Función para controlar la pantalla y el cursor
 * 
 * @param lcd 
 * @param D Enciende/apaga la pantalla (1: encendida, 0: apagada)
 * @param C Ocultar/mostrar cursor (1: mostrar, 0: ocultar)
 * @param B Parpadear cursor (1: parpadear, 0: no parpadear)
 */
void LCD_display_control(LCD *lcd, int D, int C, int B);

/**
 * @brief Función para desplazar el texto en pantalla
 * 
 * @param lcd 
 * @param SC Movimiento (1: desplazar pantalla, 0: desplazar cursor)
 * @param RL Dirección de desplazamiento (1: derecha, 0: izquierda)
 */
void LCD_cursor_display_shift(LCD *lcd, int SC, int RL);

/**
 * @brief Función para configurar la función del LCD
 * 
 * @param lcd 
 * @param DL Datos de entrada (1: 8 bits, 0: 4 bits)
 * @param N Numero de filas (1: 2 filas o 4 filas, 0: 1 fila)
 * @param F Tamaño de fuente (1: 5x10, 0: 5x8)
 */
void LCD_function_set(LCD *lcd, int DL, int N, int F);

/**
 * @brief Función para establecer la dirección de la memoria DDRAM
 * 
 * @param lcd 
 * @param address Dirección de la memoria DDRAM (0-127)
 */
void LCD_set_ddram_address(LCD *lcd, int address);

/**
 * @brief Función para escribir un dato (carácter) en el LCD
 * 
 * @param lcd 
 * @param data Carácter a escribir
 */
void  LCD_write_data(LCD *lcd, char data);

//--------------------------------------------------//

/**
 * @brief Inicialización del LCD
 * 
 * @param lcd 
 */
void LCD_inicialization_sequence(LCD *lcd);

/**
 * @brief Imprime una palabra de hasta 16 caracteres en cada línea del LCD
 * 
 * @param lcd 
 * @param word Palabra a imprimir (2 líneas de 16 caracteres cada una) el ultimo carácter debe ser '\0'
 */
void LCD_print(LCD *lcd, char word[2][17]);


#endif