//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "syshandler.h"
#include "tempdht.h"
#include "dht.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DHT sensor(PIN_DHT, DHT11);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================




void updateSensorDHT(sys_t* sys_b){
    static int error = 0;
    if( 0 == (error = sensor.readData())){
        int c = (int) sensor.ReadTemperature(CELCIUS);
        updateTempSysH(sys_b,c);
        int h = (int)  sensor.ReadHumidity();
        updateHumSysH(sys_b, h);
    }
  return;
}

//=====[Implementations of private functions]==================================
