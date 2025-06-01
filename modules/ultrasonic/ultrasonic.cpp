#include "ultrasonic.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

HCSR04::HCSR04(PinName trigPin, PinName echoPin)
    : trig(trigPin), echo(echoPin) {
    lastDistance = 0.0f;
    startTime = 0;
    echo.rise(callback(this, &HCSR04::echoRise));
    echo.fall(callback(this, &HCSR04::echoFall));
}



void HCSR04::start() {
    triggerTicker.attach(callback(this, &HCSR04::sendTriggerPulse), ULTRASONIC_SAMPLE_TIME);
}

void HCSR04::stop() {
    triggerTicker.detach(); 
}

float HCSR04::readDistance() {
    return lastDistance;
}


//=====[Implementations of private functions]==================================


void HCSR04::sendTriggerPulse() {
    trig = 0;
    wait_us(2);
    trig = 1;
    wait_us(10);
    trig = 0;
}

void HCSR04::echoRise() {
    timer.reset();
    timer.start();
    startTime = timer.elapsed_time().count();
}

void HCSR04::echoFall() {
    timer.stop();
    us_timestamp_t duration = timer.elapsed_time().count() - startTime;
    lastDistance = duration / 58.0f; // microsegundos a cm
}

