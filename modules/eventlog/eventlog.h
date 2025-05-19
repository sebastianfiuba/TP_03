//=====[#include guards - begin]===============================================

#ifndef _EVENTLOG_H_
#define _EVENTLOG_H_

//=====[Declaration of public defines]=========================================


#define INIT_LOCK_VALUE true
#define LOW_LIMIT_TEMP 15
#define MAX_HUM 80

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
  bool manual;
}log_t;
//=====[Declarations (prototypes) of public functions]=========================
/*
 init all in 0 locked 
*/
void initLog(log_t *eventlog);

/*
true if dif
false if dif
  */
bool checkLogButtons(const log_t* firstcomp, const log_t* seccomp);
/*
true if dif
false if dif
*/

bool checkChangesLockLog(const log_t* locklogcheck, const bool state);



void makeLogButtons(log_t* logbuttons, const bool but1, const bool but2);

void updateLogButtons(log_t* logsource, log_t* logobj);
void updateLogLock(log_t* locklogupd, const bool statelock);
void updateTempLog(log_t* sensorlog, int temp);
void updateHumLog(log_t* sensorlog, int hum);
void updateLedsLog(log_t* ledslog, bool statelog);
void updateSensLog(log_t* sensorlog, int sens);
void updateChangesLog(log_t* changelog, bool statechanges);
void updateManuallog(log_t* logupd, const bool state);

bool getManualLog(const log_t* elog);
bool getBut1Log(const log_t* elog);
bool getBut2Log(const log_t* elog);
bool getLed1Log(const log_t* elog);
bool getLed2Log(const log_t* elog);
int getSensLog(const log_t* elog);
int getTempLog(const log_t* elog);
int getHumLog(const log_t* elog);
bool getLockLog(const log_t* elog);
bool getChangesFlagLog(const log_t* elog);


//=====[#include guards - end]=================================================

#endif // _EVENTLOG_H_
