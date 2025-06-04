//=====[Libraries]=============================================================
#include "lock.h"


#include "arm_book_lib.h"
#include "mbed.h"
#include "syshandler.h"
#include "servo.h"



//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

servo servo(PIN_SERVO); // Conectar el servo al pin D6

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static bool checkLockConditions(sys_t* sys_a);
//=====[Implementations of public functions]===================================

void initLock(){

  changeLock(INIT_LOCK_VALUE);
}

void updateLock(sys_t* sys_a){

  
  bool statelock = checkLockConditions(sys_a);

  bool changeslock = checkChangesLockSysH(sys_a, statelock);

  if(changeslock  &&  (getManualSysH(sys_a) == CLOSED_VALUE)){
    if(getBut1SysH(sys_a))
        updateManualSysH(sys_a, OPEN_VALUE);
    changeLock(statelock);
    updateSysHLock(sys_a, statelock); //changes true
    updateChangesSysH(sys_a, true);
  }
  return;
}


void changeLock(bool state){
 
  if(state != CLOSED_VALUE){
      servo.setAngle(OPEN_ANGLE);
      return;
  }
  servo.setAngle(CLOSED_ANGLE);
  return;
}

//=====[Implementations of private functions]==================================

static bool checkLockConditions(sys_t* sys_a){

  if(getBut1SysH(sys_a)){
    return OPEN_VALUE;
  } // open

  if(getBut2SysH(sys_a)){// close
    updateManualSysH(sys_a, CLOSED_VALUE);
    return CLOSED_VALUE;
  }
  if(getSensDistSysH(sys_a) >= getDistSysH(sys_a))
    return OPEN_VALUE;
  
  int sens_aux = getSensSysH(sys_a);
  int temp_aux = getTempSysH(sys_a);
  if(LOW_LIMIT_TEMP >= temp_aux || temp_aux >= sens_aux)
    return OPEN_VALUE;
  int hum = getHumSysH(sys_a);
  if(hum >= HIGH_LIMIT_HUM)
    return OPEN_VALUE;

  return CLOSED_VALUE;
}





            
