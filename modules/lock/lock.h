//=====[#include guards - begin]===============================================

#ifndef _LOCK_H_
#define _LOCK_H_

#include "syshandler.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void initLock();
void updateLock(sys_t* sys_a);
void changeLock(bool state);

//=====[#include guards - end]=================================================

#endif // _LOCK_H_
