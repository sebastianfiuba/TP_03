//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "eventlog.h"
#include "potsens.h"


//=====[Declaration of private defines]========================================

#define BASE_TEMP  20   //in Celsius
#define MAX_TEMP   40   //in Celsius

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn limitPot(A0);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================




void updateSens(log_t* sens){
  
  int limitTemp_ant = getSensLog(sens);
  float potReading  = limitPot.read();
  int limitTemp  = (int)(potReading * (MAX_TEMP - BASE_TEMP) + BASE_TEMP);

  if (limitTemp_ant != limitTemp)
    updateSensLog(sens,limitTemp);

  return;
}

//=====[Implementations of private functions]==================================
