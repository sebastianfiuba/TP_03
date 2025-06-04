//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "syshandler.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void initSysH(sys_t* sysh){
  sysh->but1 = false;
  sysh->but2 = false;
  sysh->led1 = !INIT_LOCK_VALUE; // open
  sysh->led2 = INIT_LOCK_VALUE;
  sysh->led3 = INIT_DIST_MODE;
  sysh->lock = INIT_LOCK_VALUE;
  sysh->changes = INIT_CHANGES_VALUE;
  sysh->temp = 0;
  sysh->hum = 0;
  sysh->sens = 0;
  sysh->dist = 0;
  sysh->sensdist = INIT_SENSDIST_VALUE;
  sysh->diststate = INIT_DIST_MODE;
  sysh->manual = INIT_LOCK_VALUE;
  return;
  
}

/*
true if dif
false if dif
  */
bool checkSysHButtons(const sys_t* sysh_first, const sys_t* sysh_second){

  if(sysh_first->but1 != sysh_second-> but1)
    return false;
  if(sysh_first->but2 != sysh_second-> but2)
    return false;
  return true;
}

void makeSysHButtons(sys_t* sysh, const bool but1, const bool but2){

  sysh->but1 = but1;
  sysh->but2 = but2;
  
  return;
}

void updateSysHButtons(sys_t* sysh_ori, sys_t* sysh_obj){

  sysh_obj->but1 = sysh_ori->but1;
  sysh_obj->but2 = sysh_ori->but2;

  return;
}

/*
true if dif
false if dif
*/

bool checkChangesLockSysH(const sys_t* sysh, const bool state){

  if(sysh->lock != state)
    return true;
  
  return false;
}


void updateSysHLock(sys_t* sysh, const bool statelock){

  sysh->lock = statelock;
  updateChangesSysH(sysh, true);
  
  return;
}

void updateManualSysH(sys_t* sysh, const bool state){

  sysh->manual = state;
  
  return;
}


void updateTempSysH(sys_t* sysh, int temp){

  sysh->temp = temp;
  
  return;
}

void updateHumSysH(sys_t* sysh, int hum){

  sysh->hum = hum;
  
  return;
}
void updateSensSysH(sys_t* sysh, int sens){

  sysh->sens = sens;
  
  return;
}


void updateDistSysH(sys_t* sysh, int dist_a){

  sysh->dist = dist_a;
  
  return;
}

void updateSensDistSysH(sys_t *sysh, int dist_a){

  sysh->sensdist = dist_a;
  
  return;
}

void updateLedsSysH(sys_t* sysh, bool statelog, bool statedist){

  sysh->led1 = !statelog;
  sysh->led2 = statelog;
  sysh->led3 = statedist;
  
  return;
}

void updateChangesSysH(sys_t* sysh, bool statechanges){

  sysh->changes = statechanges;
  
  return;
}
void updateDistModeSysH(sys_t* sysh, bool statedist){

  sysh->diststate = statedist;
  
  return;
}


bool getManualSysH(const sys_t* sysh){
  
  return sysh->manual;
}

bool getBut1SysH(const sys_t* sysh){
  
  return sysh->but1;
}
bool getBut2SysH(const sys_t* sysh){
  
  return sysh->but2;
}

bool getLed1SysH(const sys_t* sysh){
  
  return sysh->led1;
}
bool getLed2SysH(const sys_t* sysh){
  
  return sysh->led2;
}
bool getLed3SysH(const sys_t* sysh){
  
  return sysh->led3;
}
int getSensSysH(const sys_t* sysh){
  
  return sysh->sens;
}

int getTempSysH(const sys_t* sysh){
  
  return sysh->temp;
}

int getHumSysH(const sys_t* sysh){
  
  return sysh->hum;
}
int getDistSysH(const sys_t* sysh){

  return sysh->dist;
}
int getSensDistSysH(const sys_t *sysh){
  
  return sysh->sensdist;
}

bool getLockSysH(const sys_t* sysh){
  
  return sysh->lock;
}


bool getDistModeSysH(const sys_t* sysh){

    return sysh->diststate;
}

bool getChangesFlagSysH(const sys_t* sysh){
  
  return sysh->changes;
}






