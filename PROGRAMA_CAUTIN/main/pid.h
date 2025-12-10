#define PID_H
#ifdef PID_H

#include "pico/stdlib.h"
#include <cstdint>

typedef struct{
    double Kp;          /**<Ganancia proporcional */
    double Ki;          /**<Ganancia Integrativa */
    double Kd;          /**<Ganancia Derivativa */
    double prevError;   /**<Error anterior */
    double integral;    /**<Integral de control */
} PIDController;

void PIDController_init(PIDController *pid, double Kp, double Ki, double Kd);

double PIDController_compute(PIDController *pid, double setpoint, double medida, double dt);

#endif