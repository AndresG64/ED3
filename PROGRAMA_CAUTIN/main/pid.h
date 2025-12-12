/**
 * @file pid.h
 * @author Andres David Quiñonez Rueda
 * @brief Declaraciones para el controlador PID
 * @version 0.1
 * @date 2025-12-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#define PID_H
#ifdef PID_H

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief Estructura para el controlador PID
 * 
 */
typedef struct{
    double Kp;          /**<Ganancia proporcional */
    double Ki;          /**<Ganancia Integrativa */
    double Kd;          /**<Ganancia Derivativa */
    double prevError;   /**<Error anterior */
    double integral;    /**<Integral de control */
    double integral_limit; /**<Límite para la integral (anti-windup) */
    double output_max;    /**<Valor máximo de salida para normalización */
} PIDController;

/**
 * @brief Función para inicializar el controlador PID con las ganancias dadas
 * 
 * @param pid 
 * @param Kp 
 * @param Ki 
 * @param Kd 
 */
void PIDController_init(PIDController *pid, double Kp, double Ki, double Kd);

/**
 * @brief Calcula la salida del controlador PID dado un setpoint, una medida y un intervalo de tiempo dt
 * 
 * @param pid 
 * @param setpoint Valor deseado del proceso
 * @param medida Valor medido del proceso
 * @param dt  Es el tiempo transcurrido desde la última llamada a esta función
 * @return double 
 */
double PIDController_compute(PIDController *pid, double setpoint, double medida, double dt);

#endif