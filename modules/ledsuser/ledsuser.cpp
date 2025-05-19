//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "eventlog.h"
#include "ledsuser.h" 

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut openLed(LED2);
DigitalOut closedLed(LED3);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void changeLeds(bool statelock);

//=====[Implementations of public functions]===================================

void initUserLeds(){

  changeLeds(INIT_LOCK_VALUE);
  
  return;
  
}

void updateUserleds(log_t* led){
  bool state = getLockLog(led);
  if(getChangesFlagLog(led)){
    changeLeds(state);
    updateLedsLog(led, state);
  }
  return;
}


//=====[Implementations of private functions]==================================

static void changeLeds(bool statelock){

  openLed = !statelock;
  closedLed = statelock;
  return;
}
