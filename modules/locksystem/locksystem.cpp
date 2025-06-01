//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "mbed.h"


#include "tempdht.h" 
#include "tempsensor.h"


#include "syshandler.h"
#include "eventlog.h"

#include "buttonsuser.h"
#include "ledsuser.h"
#include "lock.h"
#include "potsens.h"
#include "realtime.h"
#include "serialcom.h"
#include "userinterface.h"

#include "locksystem.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================
log_t log;
sys_t sys;
//dht11_t ths;
//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void  locksysInit(){

  userInterfaceInit();
  initLog(&log);
  initSysH(&sys)
  initLock();
 // initSensor(&ths, DHTPIN);
  pcSerialComInit();
}

void locksysUpdate(){

  userInterfaceUpdate(&sys);
  updateSensorDHT(&sys);
  updateLock(&sys);
  userInterfaceUpdate(&sys);
  pcSerialComUpdate(&sys);

  delay(SYSTEM_TIME_INCREMENT_MS);

}


//=====[Implementations of private functions]==================================
