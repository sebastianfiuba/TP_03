//=====[#include guards - begin]===============================================

#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

//=====[Declaration of public defines]=========================================

#include "eventlog.h"
#include "ledsuser.h"
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate(log_t* loginter);

//=====[#include guards - end]=================================================

#endif // _USERINTERFACE_H_
