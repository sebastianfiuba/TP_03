//=====[#include guards - begin]===============================================

#ifndef _LOCK_H_
#define _LOCK_H_

#include "eventlog.h"
//=====[Declaration of public defines]=========================================
#define OPEN_VALUE false
#define CLOSED_VALUE true
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void initLock();
void updateLock(log_t* locklog);
void changeLock(bool state);

//=====[#include guards - end]=================================================

#endif // _LOCK_H_
