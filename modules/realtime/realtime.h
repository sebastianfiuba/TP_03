//=====[#include guards - begin]===============================================

#ifndef _REAL_TIME_H_
#define _REAL_TIME_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

char* rtcRead();

void rtcWrite( int year, int month, int day, 
                       int hour, int minute, int second );

//=====[#include guards - end]=================================================

#endif // _REAL_TIME_H_
