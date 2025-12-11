/**
 * @file adc_setpoint.h
 * @author Andres David Quiñonez Rueda
 * @brief 
 * @version 0.1
 * @date 2025-12-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define ADC_SETPOINT_H

#ifdef ADC_SETPOINT_H
#include <stdio.h>
#include <stdlib.h>
#include "hardware/adc.h"
#include "pico/stdlib.h"

/**
 * @brief Estructura para la configuración del ADC para el setpoint
 * 
 */
typedef struct 
{
    uint16_t min_ref;    /**<Valor minimo de salida */
    uint16_t max_ref;    /**<Valor máximo de salida */
}adc_config;

typedef struct {
    uint8_t channel;       // ADC channel number
    float voltage_ref;     // Reference voltage for ADC
    adc_config config;  // Configuration parameters
 } adc_setpoint;

/**
 * @brief Función para inicializar el ADC en un pin y canal específico
 * 
 * @param setpoint_ es la estructura del setpoint
 * @param pin El pin del ADC
 * @param channel Canal del ADC
 * @return * void 
 */
 void adc_setpoint_init(adc_setpoint *setpoint_, uint8_t pin, uint8_t channel);

/**
 * @brief Función para configurar los parámetros del setpoint (Se debe llamar después de la inicialización)
 * @details Esta función establece los valores mínimo y máximo de referencia para mapear la lectura del ADC a un rango deseado.
 * @param setpoint_ Estructura del setpoint
 * @param min_ref Salida mínima
 * @param max_ref Salida máxima
 */
 void adc_setpoint_config(adc_setpoint *setpoint_, uint16_t min_ref, uint16_t max_ref);

 /**
  * @brief Función para leer el valor del ADC y mapearlo al rango deseado
  * 
  * @param setpoint_ 
  * @return float 
  */
 float adc_setpoint_read(adc_setpoint *setpoint_);

#endif