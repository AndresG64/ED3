/**
 * @file pid.c
 * @author Andres David Quiñonez Rueda
 * @brief Funciones para el controlador PID
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "pid.h"

void PIDController_init(PIDController *pid, double Kp, double Ki, double Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prevError = 0.0;
    pid->integral = 0.0;

    pid->integral_limit = 50.0;  /**<Limite de la integral para que no crezca y se sature */
}

double PIDController_compute(PIDController *pid, double setpoint, double medida, double dt) {

    double error = setpoint - medida;

    /**<Integral con anti-windup */
    /**<Se definen limites para +-  integral_limit para que en los limites como 0 o 100 no crezca indefinidamente*/
    pid->integral += error * dt;
    if(pid->integral >  pid->integral_limit) pid->integral =  pid->integral_limit;
    if(pid->integral < -pid->integral_limit) pid->integral = -pid->integral_limit;

    /**<Derivada */
    double derivative = (error - pid->prevError) / dt;

    /**<PID */
    double output =
        pid->Kp * error +
        pid->Ki * pid->integral +
        pid->Kd * derivative;

    pid->prevError = error;

    /**<Salida entre 0 y 1 */
    if (output > 1.0) output = 1.0;
    if (output < 0.0) output = 0.0;

    return output;
}