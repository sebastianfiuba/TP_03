
//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "syshandler.h"
#include "ultrasonic.h"
#include "distance.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

HCSR04 us_sensor(PIN_US_TRIG, PIN_US_ECHO);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void initDistance(){
//start sensor

    us_sensor.start();

}
void updateDistance(sys_t* sys_a){

    int dist = (int) us_sensor.readDistance();

    if(dist != getDistSysH(sys_a))
        updateDistSysH(sys_a, dist);
    
    if(getBut1SysH(sys_a) && getBut2SysH(sys_a) ){
        updateSensDistSysH(sys_a, dist);
        if(!getChangesFlagSysH(sys_a) && !getDistModeSysH(sys_a)){
            updateChangesSysH(sys_a, true);
            updateDistModeSysH(sys_a, true);
        }
        return;
    }
    if(getDistModeSysH(sys_a)){
        updateChangesSysH(sys_a, true);
        updateDistModeSysH(sys_a, false);
    }

    return;

}


//=====[Implementations of private functions]==================================
