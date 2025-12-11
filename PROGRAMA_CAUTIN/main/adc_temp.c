/**
 * @file adc_temp.c
 * @author Andres David Quiñonez Rueda
 * @brief 
 * @version 0.1
 * @date 2025-12-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adc_temp.h"

void adc_temp_init(ADCTempConfig *config, uint8_t pin, uint8_t channel) {
    adc_init();
    config->channel = channel;
    adc_gpio_init(pin); 
    adc_select_input(config->channel);

    config->referenceVoltage = 3.3f;
    config->resolution = 4096; /**<12-bit ADC*/    
    config->calibrationData = NULL; /**<Inicialmente sin datos de calibración*/
}

void adc_temp_data_set(ADCTempConfig *config) {

    static Par calibrationTable[] = {
        {   0, 0      },
        {  27, 0.8443 },
        {  50, 0.9442 },
        {  75, 1.0728 },
        { 100, 1.1637 },
        { 125, 1.2717 },
        { 150, 1.3568 },
        { 175, 1.4264 },
        { 200, 1.5422 },
        { 225, 1.6592 },
        { 250, 1.7626 },
        { 275, 1.8827 },
        { 300, 1.9574 },
        { 325, 2.0668 },
        { 350, 2.2019 },
        { 375, 2.2967 },
        { 400, 2.3890 },
        { 425, 2.4861 },
        { 450, 2.6612 },
        { 475, 2.8150 },
        { 500, 2.8929 },
        { 525, 3.0163 }
    };

    config->calibrationData = calibrationTable;
    config->tableSize = sizeof(calibrationTable) / sizeof(calibrationTable[0]);
}

uint16_t adc_temp_read_temperature(ADCTempConfig *config) {
    adc_select_input(config->channel); 
    uint16_t adcValue = adc_read(); 
    float voltage = (adcValue / (float)(config->resolution - 1)) * config->referenceVoltage;

    /**<Buscar en la tabla de calibración*/
    for (uint16_t i = 0; i < config->tableSize - 1; i++) {
        if (voltage >= config->calibrationData[i].voltage && voltage <= config->calibrationData[i + 1].voltage) {
            /**<Interpolación lineal (slope es la pendiente)*/
            float slope = (config->calibrationData[i + 1].temperature - config->calibrationData[i].temperature) /
                          (config->calibrationData[i + 1].voltage - config->calibrationData[i].voltage);
            float temperature = config->calibrationData[i].temperature +
                                slope * (voltage - config->calibrationData[i].voltage);
            return (uint16_t)temperature;
        }
    }

    /**<Si no se encuentra en la tabla, devolver 0 o un valor de error*/
    return 0;
}

