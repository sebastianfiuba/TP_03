//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "eventlog.h"
#include "tempdht.h"
#include "dht.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DHT sensor(D4, DHT11);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================




void updateSensorDHT(log_t* sensorlog){
    static int error = 0;
    if( 0 == (error = sensor.readData())){
        int c = (int) sensor.ReadTemperature(CELCIUS);
        updateTempLog(sensorlog,c);
        int h = (int)  sensor.ReadHumidity();
        updateHumLog(sensorlog, h);
    }
  return;
}

//=====[Implementations of private functions]==================================
