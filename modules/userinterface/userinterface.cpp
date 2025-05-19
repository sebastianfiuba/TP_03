//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "userinterface.h"
#include "eventlog.h"
#include "potsens.h"
#include "ledsuser.h"
#include "buttonsuser.h"


//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================


//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

void userInterfaceInit(){

  initUserLeds();
  initButtons();

  return;
  
}

void userInterfaceUpdate(log_t* loginter){
  
  updateButtons(loginter);
  updateUserleds(loginter);
  updateSens(loginter);

  return;

}

//=====[Implementations of private functions]==================================








