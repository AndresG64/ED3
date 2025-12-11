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

typedef struct
{
    float temperature;   /**<Temperatura */
    float voltage;       /**<Voltaje */
}Par;

typedef struct {
    uint8_t channel;        /**<ADC channel number */
    float referenceVoltage; /**<Reference voltage for ADC */
    uint16_t resolution;    /**<ADC resolution (e.g., 4096 for 12-bit) */
    Par *calibrationData;   /**<Tabla de caracterización */
    uint16_t tableSize;     /**<Tamaño de la tabla de caracterización */
} ADCTempConfig;

void adc_temp_init(ADCTempConfig *config, uint8_t pin, uint8_t channel);

void adc_temp_data_set(ADCTempConfig *config);

uint16_t adc_temp_read_temperature(ADCTempConfig *config);

#endif