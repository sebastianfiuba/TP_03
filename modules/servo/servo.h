//=====[#include guards - begin]===============================================
#ifndef _SERVO_H_
#define _SERVO_H_
//=====[Declaration of public defines]=========================================
#include "mbed.h"
#include "arm_book_lib.h"


//=====[Declaration of public data types]======================================

class servo {
public:
    servo (PinName pwmPin);
    void setAngle(float angle); // ángulo en grados (0 a 180)

private:
    PwmOut pwm;
};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================


#endif// _SERVO_H_





