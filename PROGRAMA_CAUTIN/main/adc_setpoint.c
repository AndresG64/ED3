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

/**
 * @brief Función para inicializar el ADC en un pin y canal específico
 * 
 * @param setpoint_ 
 * @param pin 
 * @param channel 
 */
void adc_setpoint_init(adc_setpoint *setpoint_, uint8_t pin, uint8_t channel){
    adc_init();                         /**<Inicializamos el adc */
    setpoint_->channel = channel;       /**<Asignamos el canal a la estrucctura */
    adc_gpio_init(pin);                 /**<Habilitamos el pin para el ADC */
    adc_select_input(setpoint_->channel);    /**<Seleccionamos el canal, este corresponde al pin que se va habilitar */
}

/**
 * @brief Función para configurar los parámetros del setpoint
 * 
 * @param setpoint_ 
 * @param min_ref 
 * @param max_ref 
 */
void adc_setpoint_config(adc_setpoint *setpoint_, uint8_t min_ref, uint8_t max_ref){
    setpoint_->config.min_ref = min_ref;
    setpoint_->config.max_ref = max_ref;
}

/**
 * @brief Función para leer el valor del ADC y mapearlo al rango deseado
 * 
 * @param setpoint_ 
 * @return float 
 */
float adc_setpoint_read(adc_setpoint *setpoint_){
    uint16_t value = adc_read();                                /**<Leemos el valor del ADC */
    float calc = setpoint_->config.min_ref + ((float)value / 4095.0f) * (setpoint_->config.max_ref - setpoint_->config.min_ref);    /**<Mapeamos el valor al rango deseado */
    return calc;
}

/**<adc_read(); */