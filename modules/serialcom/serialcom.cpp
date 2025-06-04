//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "serialcom.h"

#include "syshandler.h"
#include "eventlog.h"
#include "lock.h"
#include "realtime.h"
#include "ledsuser.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================


//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================
static void pcSerialComStringRead(char* str, int strLength);
static void pcSerialComCommandUpdate(char receivedChar, sys_t* sys_a, log_t* log_a);
static void availableCommands();
static void commandShowCurrentLockState(const sys_t* sys_a);
static void commandShowCurrentButtonsState(const sys_t* sys_a);
static void commandShowCurrentLedsState(const sys_t* sys_a);
static void commandShowCurrentTemp(const sys_t* sys_a);
static void commandShowCurrentHum(const sys_t* sys_a);
static void commandShowCurrentSens(const sys_t* sys_a);
static void commandShowCurrentDist(const sys_t* sys_a);
static void commandOpenLock(sys_t* sys_a);
static void commandCloseLock(sys_t* sys_a);
static void commandSetDateAndTime();
static void commandShowDateAndTime();
static void commandShowCurrentLog(log_t* log_b, const sys_t* sys_a);


//=====[Implementations of public functions]===================================

void pcSerialComInit(){
  availableCommands();
}

char pcSerialComCharRead(){
  char receivedChar = '\0';
  if( uartUsb.readable() ) {
    uartUsb.read(&receivedChar,1);
  }
  return receivedChar;
}

void pcSerialComStringWrite(const char* str){
  uartUsb.write( str, strlen(str) );
  return;
}

void pcSerialComUpdate(sys_t* sys_a, log_t* log_a){
  char receivedChar = pcSerialComCharRead();
  if( receivedChar != '\0' ) {
    pcSerialComCommandUpdate(receivedChar, sys_a, log_a);
  }    
  if(getChangesFlagSysH(sys_a)){
    commandShowCurrentLog(log_a, sys_a);
    updateChangesSysH(sys_a, false);
    updateLog(sys_a, log_a);
  }

  return;
}



//=====[Implementations of private functions]==================================

static void pcSerialComStringRead(char* str, int strLength){
  int strIndex;
  for ( strIndex = 0; strIndex < strLength; strIndex++){
    uartUsb.read( &str[strIndex] , 1 );
    uartUsb.write( &str[strIndex] ,1 );
  }
  str[strLength]='\0';
}


static void pcSerialComCommandUpdate(char receivedChar, sys_t* sys_a, log_t* log_a){
  switch (receivedChar){
    case '1': commandShowCurrentLockState(sys_a); break;
    case '2': commandShowCurrentButtonsState(sys_a); break;
    case '3': commandShowCurrentLedsState(sys_a); break;
    case '4': availableCommands(); break;
    case 'o': case 'O': commandOpenLock(sys_a); break;
    case 'c': case 'C': commandCloseLock(sys_a); break;
    case 't': case 'T': commandShowCurrentTemp(sys_a); break;
    case 'm': case 'M': commandShowCurrentSens(sys_a); break;
    case 'f': case 'F': commandShowCurrentDist(sys_a); break;
    case 'h': case 'H': commandShowCurrentHum(sys_a); break;
    case 's': case 'S': commandSetDateAndTime(); break;
    case 'd': case 'D': commandShowDateAndTime(); break;
    case 'l': case 'L': commandShowCurrentLog(log_a, sys_a); break;

    default: availableCommands(); break;
    } 
}

static void availableCommands(){
  pcSerialComStringWrite( "Available commands:\r\n" );
  pcSerialComStringWrite( "Press '1' to get the lock state\r\n" );
  pcSerialComStringWrite( "Press '2' to get the buttons states\r\n" );
  pcSerialComStringWrite( "Press '3' to get the leds states\r\n" );
  pcSerialComStringWrite( "Press '4' to show available commands\r\n" );
  pcSerialComStringWrite( "Press 'o' or 'O' to open the lock \r\n" );
  pcSerialComStringWrite( "Press 'c' or 'C' to close the lock \r\n" );
  pcSerialComStringWrite( "Press 't' or 'T' to get the current temperature reading\r\n" );
  pcSerialComStringWrite( "Press 'h' or 'H' to get the current humidity reading\r\n" );
  pcSerialComStringWrite( "Press 'f' or 'F' to get the current distance reading\r\n" );
  pcSerialComStringWrite( "Press 'm' or 'M' to get the current limits\r\n" );
  pcSerialComStringWrite( "Press 's' or 'S'  to set the date and time\r\n" );
  pcSerialComStringWrite( "Press 'd' or 'D' to get the date and time\r\n" );
  pcSerialComStringWrite( "Press 'l' or 'L' to get the current log update\r\n" );
  pcSerialComStringWrite( "\r\n" );
}

static void commandShowCurrentLockState(const sys_t* sys_a){
  if (!getLockSysH(sys_a)){
    pcSerialComStringWrite( "The lock is open\r\n");
  }
  else{
      pcSerialComStringWrite( "The lock is closed\r\n");
  }
  return;
}
static void commandShowCurrentButtonsState(const sys_t* sys_a){
  if (getBut1SysH(sys_a)){
    pcSerialComStringWrite( "The button 1 is pressed\r\n");
  }
  else{
    pcSerialComStringWrite( "The button 1 is not pressed\r\n");
  }
  if (getBut2SysH(sys_a)){
    pcSerialComStringWrite( "The button 2 is pressed\r\n");
  }
  else{
    pcSerialComStringWrite( "The button 2 is not pressed\r\n");
  }
  return;
}

static void commandShowCurrentLedsState(const sys_t* sys_a){
  if (getLed1SysH(sys_a)){
    pcSerialComStringWrite( "The Led 1 is on\r\n");
  }
  else{
    pcSerialComStringWrite( "The Led 1 is off\r\n");
  }
  if (getLed2SysH(sys_a)){
    pcSerialComStringWrite( "The Led 2 is on\r\n");
  }
  else{
    pcSerialComStringWrite( "The Led 2 is off\r\n");
  }
  if (getLed3SysH(sys_a)){
    pcSerialComStringWrite( "The Led 3 is on\r\n");
  }
  else{
    pcSerialComStringWrite( "The Led 3 is off\r\n");
  }
  return;
}


static void commandShowCurrentTemp(const sys_t* sys_a){
  char str[100] = "";
  sprintf ( str, "Temperature: %d \xB0 C\r\n", getTempSysH(sys_a) );
  pcSerialComStringWrite( str );  
  return;
}

static void commandShowCurrentHum(const sys_t* sys_a){
  char str[100] = "";
  sprintf ( str, "Humidity: %d %% \r\n", getHumSysH(sys_a) );
  pcSerialComStringWrite( str );  
  return;
}

static void commandShowCurrentSens(const sys_t* sys_a){
  char str[100] = "";
  sprintf ( str, "The minimum temperature is %d \xB0 C and the maximum temperature is %d \xB0 C\r\n", LOW_LIMIT_TEMP ,getSensSysH(sys_a) );
  pcSerialComStringWrite( str ); 
  sprintf(str, "The maximum humidity is: %d %%\r\n", MAX_HUM);
  pcSerialComStringWrite( str ); 
  sprintf(str, "The maximum distance from the lock to open it is: %d cm \r\n", getSensDistSysH(sys_a));
  pcSerialComStringWrite( str ); 
  return; 
}

static void commandShowCurrentDist(const sys_t* sys_a){

  char str[100] = "";
  sprintf ( str, "Distance: %d cm \r\n", getDistSysH(sys_a) );
  pcSerialComStringWrite( str ); 
  if(getDistModeSysH(sys_a)){
    pcSerialComStringWrite("Distance and limits are being meseaured\r\n");
    return;
  }
    pcSerialComStringWrite("Only distance is being meseaured\r\n");
  return;
}
static void commandOpenLock(sys_t* sys_a){
  updateSysHLock(sys_a, OPEN_VALUE);
  updateManualSysH(sys_a, OPEN_VALUE);
  updateChangesSysH(sys_a, true);
  changeLock(OPEN_VALUE);
  updateUserleds(sys_a);
  return;
}

static void commandCloseLock(sys_t* sys_a){
  
  updateSysHLock(sys_a, CLOSED_VALUE);
  updateManualSysH(sys_a, CLOSED_VALUE);
  updateChangesSysH(sys_a, true);
  changeLock(CLOSED_VALUE);
  updateUserleds(sys_a);
  return;
}

static void commandSetDateAndTime(){
    char year[5] = "";
    char month[3] = "";
    char day[3] = "";
    char hour[3] = "";
    char minute[3] = "";
    char second[3] = "";
    
    pcSerialComStringWrite("\r\nType four digits for the current year (YYYY): ");
    pcSerialComStringRead( year, 4);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current month (01-12): ");
    pcSerialComStringRead( month, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current day (01-31): ");
    pcSerialComStringRead( day, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current hour (00-23): ");
    pcSerialComStringRead( hour, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current minutes (00-59): ");
    pcSerialComStringRead( minute, 2);
    pcSerialComStringWrite("\r\n");

    pcSerialComStringWrite("Type two digits for the current seconds (00-59): ");
    pcSerialComStringRead( second, 2);
    pcSerialComStringWrite("\r\n");
    
    pcSerialComStringWrite("Date and time has been set\r\n");

    rtcWrite( atoi(year), atoi(month), atoi(day), 
        atoi(hour), atoi(minute), atoi(second) );
}

static void commandShowDateAndTime(){
    char str[100] = "";
    sprintf ( str, "Date and Time = %s", rtcRead() );
    pcSerialComStringWrite( str );
    pcSerialComStringWrite("\r\n");
    return;
}

static void commandShowCurrentLog(log_t* log_b, const sys_t* sys_a){

  updateLog(sys_a, log_b);

  char stri [100] = "\r\nstart of message:\r\n";
  char strf [100] = "end of message.\r\n";
  pcSerialComStringWrite( stri );

  commandShowCurrentLockState(sys_a);
  commandShowCurrentButtonsState(sys_a);
  commandShowCurrentLedsState(sys_a);
  commandShowCurrentTemp(sys_a);
  commandShowCurrentHum(sys_a);
  commandShowCurrentSens(sys_a);
  commandShowCurrentDist(sys_a);
  commandShowDateAndTime();
  pcSerialComStringWrite(strf);
  return;
}
