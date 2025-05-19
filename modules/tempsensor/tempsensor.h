//=====[#include guards - begin]===============================================
#ifndef _TEMPSENSOR_H_
#define _TEMPSENSOR_H_

#include "eventlog.h"
#include "mbed.h"

//=====[Declaration of public defines]=========================================


typedef struct {
    PinName pin;
    DigitalInOut* data;
    int temperature;
    int humidity;
} dht11_t;

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void initSensor(dht11_t* sensor, PinName pin);
void updateSensor(log_t* sensorlog, dht11_t* sensor1);

//=====[#include guards - end]=================================================

#endif // _TEMPSENSOR_H_
