//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "userinterface.h"
#include "syshandler.h"
#include "potsens.h"
#include "ledsuser.h"
#include "buttonsuser.h"
#include "distance.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================


//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

void userInterfaceInit(){

  initButtons();
  initUserLeds();
  initDistance();

  return;
  
}

void userInterfaceUpdate(sys_t* sys_a){
  
  updateButtons(sys_a);
  updateSens(sys_a);
  updateDistance(sys_a);
  updateUserleds(sys_a);

  return;

}

//=====[Implementations of private functions]==================================








