/**
 * @file adc_temp.h
 * @author Andres David Quiñonez Rueda
 * @brief 
 * @version 0.1
 * @date 2025-12-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define ADC_TEMP_H
#ifdef ADC_TEMP_H
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware/adc.h"
/**
 * @brief Estruct para pares de temperatura y voltaje
 * 
 */
typedef struct
{
    float temperature;   /**<Temperatura */
    float voltage;       /**<Voltaje */
}Par;

/**
 * @brief Estruct para configuración del sensor de temperatura ADC
 * 
 */
typedef struct {
    uint8_t channel;        /**<ADC channel number */
    float referenceVoltage; /**<Reference voltage for ADC */
    uint16_t resolution;    /**<ADC resolution (e.g., 4096 for 12-bit) */
    Par *calibrationData;   /**<Tabla de caracterización */
    uint16_t tableSize;     /**<Tamaño de la tabla de caracterización */
} ADCTempConfig;

/**
 * @brief Función para inicializar el ADC para lectura de temperatura
 * @details Configura el ADC en el pin y canal especificados, y establece los parámetros básicos.
 * @param config 
 * @param pin 
 * @param channel 
 */
void adc_temp_init(ADCTempConfig *config, uint8_t pin, uint8_t channel);

/**
 * @brief Función para establecer los datos de calibración de temperatura
 * @details Carga una tabla de calibración predefinida en la estructura de configuración que se extrajo de la hoja de calculo
 * @param config 
 */
void adc_temp_data_set(ADCTempConfig *config);

/**
 * @brief Función para leer la temperatura desde el ADC
 * @details Lee el valor del ADC, convierte a voltaje y utiliza la tabla de calibración para interpolar la temperatura. T = T1 + slope * (V - V1)
 *      Si el voltaje no está en el rango de la tabla, devuelve 0. Slope: pendiente entre dos puntos de calibración.
 * @param config 
 * @return uint16_t 
 */
uint16_t adc_temp_read_temperature(ADCTempConfig *config);

#endif