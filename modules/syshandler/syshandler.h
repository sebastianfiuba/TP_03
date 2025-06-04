//=====[#include guards - begin]===============================================
#ifndef _SYSHANDLER_H_
#define _SYSHANDLER_H_

//=====[Declaration of public defines]=========================================


#define OPEN_VALUE false
#define CLOSED_VALUE true

#define INIT_LOCK_VALUE CLOSED_VALUE
#define LOW_LIMIT_TEMP 15
#define MAX_HUM 80
#define HIGH_LIMIT_HUM MAX_HUM
#define INIT_SENSDIST_VALUE 25
#define INIT_CHANGES_VALUE true
#define INIT_DIST_MODE false


#define OPEN_ANGLE 180.0f
#define CLOSED_ANGLE 90.0f


#define PIN_OPEN_BUTTON D2
#define PIN_CLOSE_BUTTON D3
#define PIN_DHT D4
#define PIN_SERVO D5
#define PIN_US_TRIG D6
#define PIN_US_ECHO D7


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
}sys_t;
//=====[Declarations (prototypes) of public functions]=========================
/*
 init all in 0 locked 
*/
void initSysH(sys_t* sysh);

/*
true if dif
false if dif
  */
bool checkSysHButtons(const sys_t* sysh_first, const sys_t* sysh_second);
/*
true if dif
false if dif
*/

bool checkChangesLockSysH(const sys_t* sysh, const bool state);



void makeSysHButtons(sys_t* sysh, const bool but1, const bool but2);

void updateSysHButtons(sys_t* sysh_ori, sys_t* sysh_obj);
void updateSysHLock(sys_t* sysh, const bool statelock);
void updateTempSysH(sys_t* sysh, int temp);
void updateHumSysH(sys_t* sysh, int hum);
void updateLedsSysH(sys_t* sysh, bool statelog, bool statedist);
void updateSensSysH(sys_t* sysh, int sens);
void updateDistSysH(sys_t* sysh, int dist_a);
void updateSensDistSysH(sys_t *sysh, int dist_a);
void updateChangesSysH(sys_t* sysh, bool statechanges);
void updateManualSysH(sys_t* sysh, const bool state);
void updateDistModeSysH(sys_t* sysh, bool statedist);

bool getManualSysH(const sys_t* sysh);
bool getBut1SysH(const sys_t* sysh);
bool getBut2SysH(const sys_t* sysh);
bool getLed1SysH(const sys_t* sysh);
bool getLed2SysH(const sys_t* sysh);
bool getLed3SysH(const sys_t* sysh);
int getSensSysH(const sys_t* sysh);
int getTempSysH(const sys_t* sysh);
int getHumSysH(const sys_t *sysh);
int getDistSysH(const sys_t* sysh);
int getSensDistSysH(const sys_t *sysh);
bool getLockSysH(const sys_t* sysh);
bool getChangesFlagSysH(const sys_t* sysh);
bool getDistModeSysH(const sys_t* sysh);

//=====[#include guards - end]=================================================

#endif // _SYSHANDLER_H_
