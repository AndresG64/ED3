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
#include <cstdint>
#include "hardware/adc.h"
#include "pico/stdlib.h"

struct adc_config
{
    uint8_t min_ref;    /**<Valor minimo de salida */
    uint8_t max_ref;    /**<Valor máximo de salida */
};


typedef struct {
    uint8_t channel;       // ADC channel number
    adc_input_t input;     // ADC input configuration
    float voltage_ref;     // Reference voltage for ADC
    adc_config config;  // Configuration parameters
 } adc_setpoint;


 void adc_setpoint_unit(adc_setpoint *setpoint_, uint8_t pin, uint8_t channel);

 void adc_setpoint_config(adc_setpoint *setpoint_, uint8_t min_ref, uint8_t max_ref);

 float adc_setpoint_read(adc_setpoint *setpoint_);

#endif