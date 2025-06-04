
#include "mbed.h"
#include "arm_book_lib.h"
#include "servo.h"

//=====[Declaration of private defines]========================================

#define PWM_PERIOD 20
#define INIT_ANGLE 0

#define LOW_LIMIT_ANGLE 0.0f
#define HIGH_LIMIT_ANGLE 180.0f

#define MICRO_TO_MILI 1000

//=====[Declaration of private data types]=====================================



//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================
servo::servo(PinName pwmPin) : pwm(pwmPin) {
    pwm.period_ms(PWM_PERIOD); // 20 ms = 50 Hz
    setAngle(INIT_ANGLE);       // posición inicial
}


void servo::setAngle(float angle) {
    // Limitar el ángulo entre 0 y 180
    if (angle < LOW_LIMIT_ANGLE) angle = LOW_LIMIT_ANGLE;
    if (angle > HIGH_LIMIT_ANGLE) angle = HIGH_LIMIT_ANGLE;

    // Convertir ángulo a ancho de pulso (duty cycle)
    float pulseWidthMs = 0.5f + (angle / HIGH_LIMIT_ANGLE)*2; // entre 1 ms y 1.5 ms
    pwm.pulsewidth_us(pulseWidthMs*MICRO_TO_MILI);
}


//=====[Implementations of private functions]==================================
