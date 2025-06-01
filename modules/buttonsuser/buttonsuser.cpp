
//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "syshandler.h"
#include "buttonsuser.h"


//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME_MS 100
//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//busin no parece necesario

DigitalIn openButton(PIN_OPEN_BUTTON);
DigitalIn closeButton(PIN_CLOSE_BUTTON);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static bool debounceButtons(sys_t* sys);
static void readButtons(sys_t* readlog);



//=====[Implementations of public functions]===================================

void initButtons(){

  closeButton.mode(PullDown);
  openButton.mode(PullDown);
  
  return;
}

void updateButtons(sys_t* sys_b){

  sys_t first_aux;
  initSysH(&first_aux);
  readButtons(&first_aux);
  
    if (!checkSysHButtons(&first_aux, sys_b))
      if (debounceButtons(&first_aux))
        updateSysHButtons(&first_aux, sys_b);
  
    
  return;
}


//=====[Implementations of private functions]==================================
//interrupts?
static bool debounceButtons(sys_t* sys_c){

  
    delay(DEBOUNCE_TIME_MS);
    sys_t second;
    readButtons(&second);


    return checkSysHButtons(sys_c, &second);

}

static void readButtons(sys_t* sys_d){

    bool button1 = openButton;
    bool button2 = closeButton;
    
    makeSysHButtons(sys_d, button1, button2);

    return;
}

