#include "pid.h"

PIDController_init(PIDController *pid, double Kp, double Ki, double Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prevError = 0.0;
    pid->integral = 0.0;
}

double PIDController_compute(PIDController *pid, double setpoint, double medida, double dt) {
    double error = setpoint - medida;   /**<Error calculado */
    pid->integral += error * dt;    /**<Integral actualizada, va sumando el error en cada lectura anterior */
    double derivative = (error - pid->prevError) / dt;  /**<La acción de derivar aumenta o disminuye la acción del cambio  */
    double output = (pid->Kp * error) + (pid->Ki * pid->integral) + (pid->Kd * derivative); /**<Salida del controlador PID */
    pid->prevError = error; /**<Actualizar el error anterior */
    return output;  /**<Retornar la salida del controlador */
}