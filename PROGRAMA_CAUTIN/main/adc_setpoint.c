/**
 * @file adc_setpoint.c
 * @author Andres David Quiñonez Rueda
 * @brief 
 * @version 0.1
 * @date 2025-12-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adc_setpoint.h"

void adc_setpoint_unit(adc_setpoint *setpoint_, uint8_t pin, uint8_t channel){
    adc_init();                         /**<Inicializamos el adc */
    setpoint_->channel = channel;       /**<Asignamos el canal a la estrucctura */
    adc_gpio_init(pin);                 /**<Habilitamos el pin para el ADC */
    adc_select_input(adc_->channel);    /**<Seleccionamos el canal, este corresponde al pin que se va habilitar */
}

void adc_setpoint_config(adc_setpoint *setpoint_, uint8_t min_ref, uint8_t max_ref){
    setpoint_->config.min_ref = min_ref;
    setpoint_->config.max_ref = max_ref;
}

float adc_setpoint_read(adc_setpoint *setpoint_){
    uint16_t value = adc_read();                                /**<Leemos el valor del ADC */
    float calc = setpoint_->config.min_ref + ((float)value / 4095.0f) * (setpoint_->config.max_ref - setpoint_->config.min_ref);    /**<Mapeamos el valor al rango deseado */
    return calc;
}

/**<adc_read(); */