//=====[#include guards - begin]===============================================

#ifndef _EVENTLOG_H_
#define _EVENTLOG_H_

#include "syshandler.h"

//=====[Declaration of public defines]=========================================


//=====[Declaration of public data types]======================================
typedef struct{
  bool but1; 
  bool but2;
  bool led1;
  bool led2;
  bool led3;
  bool lock;  
  bool changes;
  int temp;
  int hum;
  int sens;
  int dist;
  int sensdist;
  bool diststate;
  bool manual;
}log_t;
//=====[Declarations (prototypes) of public functions]=========================

void updateLog(const sys_t* sys_c, log_t* log_c);
void initLog(const sys_t* sys_a, log_t* log_a);

//=====[#include guards - end]=================================================

#endif // _EVENTLOG_H_
