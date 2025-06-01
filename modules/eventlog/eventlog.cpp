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

void updateLog(const sys_t* sys_c, log_t* log_c){

  log_c->but1 = sys_c->but1;
  log_c->but2 = sys_c->but2;
  log_c->led1 = sys_c->led1; 
  log_c->led2 = sys_c->led2;
  log_c->led3 = sys_c->led3;
  log_c->lock = sys_c->lock;
  log_c->changes = sys_c->changes;
  log_c->temp = sys_c->temp;
  log_c->hum = sys_c->hum;
  log_c->sens = sys_c->sens;
  log_c->dist = sys_c->dist;
  log_c->diststate = sys_c->diststate;
  log_c->sensdist = sys_c->sensdist;
  log_c->manual = sys_c->manual;

  return;

}

void initLog(const sys_t* sys_a, log_t* log_a){
    updateLog(sys_a, log_a);
    return;
}