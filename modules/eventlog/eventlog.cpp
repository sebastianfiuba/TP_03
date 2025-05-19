//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "eventlog.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void initLog(log_t *eventlog){
  eventlog->but1 = false;
  eventlog->but2 = false;
  eventlog->led1 = !INIT_LOCK_VALUE; // open
  eventlog->led2 = INIT_LOCK_VALUE;
  eventlog->lock = INIT_LOCK_VALUE;
  eventlog->changes = false;
  eventlog->temp = 0;
  eventlog->hum = 0;
  eventlog->sens = 0;
  eventlog->manual = !INIT_LOCK_VALUE;
  return;
  
}

/*
true if dif
false if dif
  */
bool checkLogButtons(const log_t* firstcomp, const log_t* seccomp){

  if(firstcomp->but1 != seccomp-> but1)
    return false;
  if(firstcomp->but2 != seccomp-> but2)
    return false;
  return true;
}

void makeLogButtons(log_t* logbuttons, const bool but1, const bool but2){

  logbuttons->but1 = but1;
  logbuttons->but2 = but2;
  
  return;
}

void updateLogButtons(log_t* logsource, log_t* logobj){

  logobj->but1 = logsource->but1;
  logobj->but2 = logsource->but2;

  return;
}

/*
true if dif
false if dif
*/

bool checkChangesLockLog(const log_t* locklogcheck, const bool state){

  if(locklogcheck->lock != state)
    return true;
  
  return false;
}


void updateLogLock(log_t* locklogupd, const bool statelock){

  locklogupd->lock = statelock;
  updateChangesLog(locklogupd, true);
  
  return;
}

void updateManuallog(log_t* logupd, const bool state){

  logupd->manual = state;
  
  return;
}


void updateTempLog(log_t* sensorlog, int temp){

  sensorlog->temp = temp;
  
  return;
}

void updateHumLog(log_t* sensorlog, int hum){

  sensorlog->hum = hum;
  
  return;
}
void updateSensLog(log_t* sensorlog, int sens){

  sensorlog->sens = sens;
  
  return;
}

void updateLedsLog(log_t* ledslog, bool statelog){

  ledslog->led1 = !statelog;
  ledslog->led2 = statelog;
  
  return;
}

void updateChangesLog(log_t* changelog, bool statechanges){

  changelog->changes = statechanges;
  
  return;
}


bool getManualLog(const log_t* elog){
  
  return elog->manual;
}

bool getBut1Log(const log_t* elog){
  
  return elog->but1;
}
bool getBut2Log(const log_t* elog){
  
  return elog->but2;
}

bool getLed1Log(const log_t* elog){
  
  return elog->led1;
}
bool getLed2Log(const log_t* elog){
  
  return elog->led2;
}
int getSensLog(const log_t* elog){
  
  return elog->sens;
}

int getTempLog(const log_t* elog){
  
  return elog->temp;
}

int getHumLog(const log_t* elog){
  
  return elog->hum;
}

bool getLockLog(const log_t* elog){
  
  return elog->lock;
}

bool getChangesFlagLog(const log_t* elog){
  
  return elog->changes;
}






