//=====[#include guards - begin]===============================================
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#include "mbed.h"
#include "arm_book_lib.h"
//=====[Declaration of public defines]=========================================

#define ULTRASONIC_SAMPLE_TIME 100ms

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

class HCSR04 {
public:
    HCSR04(PinName trigPin, PinName echoPin);
    float readDistance(); 
    void start();           
    void stop();

private:
    DigitalOut trig;
    InterruptIn echo;
    Timer timer;
    Ticker triggerTicker;

    float lastDistance;
    void sendTriggerPulse();
    void echoRise();
    void echoFall();
    us_timestamp_t startTime;
};



//=====[#include guards - end]=================================================
#endif // _ULTRASONIC_H_