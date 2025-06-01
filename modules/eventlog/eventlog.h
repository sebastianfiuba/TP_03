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
  bool lock;  
  bool changes;
  int temp;
  int hum;
  int sens;
  int dist;
  int sensdist;
  bool manual;
}log_t;
//=====[Declarations (prototypes) of public functions]=========================

void updateLog(sys_t* sys_c, log_t* log_c);

//=====[#include guards - end]=================================================

#endif // _EVENTLOG_H_
