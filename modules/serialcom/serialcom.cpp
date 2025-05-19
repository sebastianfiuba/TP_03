//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "serialcom.h"

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
static void pcSerialComCommandUpdate(char receivedChar, log_t* log);
static void availableCommands();
static void commandShowCurrentLockState(const log_t* log);
static void commandShowCurrentButtonsState(const log_t* log);
static void commandShowCurrentLedsState(const log_t* log);
static void commandShowCurrentTemp(const log_t* log);
static void commandShowCurrentHum(const log_t* log);
static void commandShowCurrentSens(const log_t* log);
static void commandOpenLock(log_t* log);
static void commandCloseLock(log_t* log);
static void commandSetDateAndTime();
static void commandShowDateAndTime();
static void commandShowCurrentLog(const log_t* logc);


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

void pcSerialComUpdate(log_t* loga){
  char receivedChar = pcSerialComCharRead();
  if( receivedChar != '\0' ) {
    pcSerialComCommandUpdate(receivedChar, loga);
  }    
  if(getChangesFlagLog(loga)){
    commandShowCurrentLog(loga);
    updateChangesLog(loga,false);
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


static void pcSerialComCommandUpdate(char receivedChar, log_t* log){
  switch (receivedChar){
    case '1': commandShowCurrentLockState(log); break;
    case '2': commandShowCurrentButtonsState(log); break;
    case '3': commandShowCurrentLedsState(log); break;
    case '4': availableCommands(); break;
    case 'o': case 'O': commandOpenLock(log); break;
    case 'c': case 'C': commandCloseLock(log); break;
    case 't': case 'T': commandShowCurrentTemp(log); break;
    case 'm': case 'M': commandShowCurrentSens(log); break;
    case 'h': case 'H': commandShowCurrentHum(log); break;
    case 's': case 'S': commandSetDateAndTime(); break;
    case 'd': case 'D': commandShowDateAndTime(); break;
    case 'l': case 'L': commandShowCurrentLog(log); break;
 
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
  pcSerialComStringWrite( "Press 'm' or 'M' to get the current humidity reading\r\n" );
  pcSerialComStringWrite( "Press 'h' or 'H' to get the current humidity reading\r\n" );
  pcSerialComStringWrite( "Press 's' or 'S' to set the date and time\r\n" );
  pcSerialComStringWrite( "Press 'd' or 'D' to get the date and time\r\n" );
  pcSerialComStringWrite( "Press 'l' or 'L' to get the current log update\r\n" );
  pcSerialComStringWrite( "\r\n" );
}

static void commandShowCurrentLockState(const log_t* log){
  if (!getLockLog(log)){
    pcSerialComStringWrite( "The lock is open\r\n");
  }
  else{
      pcSerialComStringWrite( "The lock is closed\r\n");
  }
  return;
}
static void commandShowCurrentButtonsState(const log_t* log){
  if (getBut1Log(log)){
    pcSerialComStringWrite( "The button 1 is pressed\r\n");
  }
  else{
    pcSerialComStringWrite( "The button 1 is not pressed\r\n");
  }
  if (getBut2Log(log)){
    pcSerialComStringWrite( "The button 2 is pressed\r\n");
  }
  else{
    pcSerialComStringWrite( "The button 2 is not pressed\r\n");
  }
  return;
}

static void commandShowCurrentLedsState(const log_t* log){
  if (getLed1Log(log)){
    pcSerialComStringWrite( "The Led 1 is on\r\n");
  }
  else{
    pcSerialComStringWrite( "The Led 1 is off\r\n");
  }
  if (getLed2Log(log)){
    pcSerialComStringWrite( "The Led 2 is on\r\n");
  }
  else{
    pcSerialComStringWrite( "The Led 2 is off\r\n");
  }
  return;
}


static void commandShowCurrentTemp(const log_t* log){
  char str[100] = "";
  sprintf ( str, "Temperature: %d \xB0 C\r\n", getTempLog(log) );
  pcSerialComStringWrite( str );  
  return;
}

static void commandShowCurrentHum(const log_t* log){
  char str[100] = "";
  sprintf ( str, "Humidity: %d %% \r\n", getHumLog(log) );
  pcSerialComStringWrite( str );  
  return;
}

static void commandShowCurrentSens(const log_t* log){
  char str[100] = "";
  sprintf ( str, "The minimum temperature is %d \xB0 C and the maximum temperature is %d \xB0 C\r\n", LOW_LIMIT_TEMP ,getSensLog(log) );
  pcSerialComStringWrite( str ); 
  sprintf(str, "The maximum humidity is: %d %%\r\n", MAX_HUM);
  pcSerialComStringWrite( str ); 
  return; 
}
static void commandOpenLock(log_t* log){
  updateLogLock(log, OPEN_VALUE);
  updateManuallog(log, !OPEN_VALUE);
  updateChangesLog(log, true);
  changeLock(OPEN_VALUE);
  updateUserleds(log);
  return;
}

static void commandCloseLock(log_t* log){
  
  updateLogLock(log, CLOSED_VALUE);
  updateManuallog(log, !CLOSED_VALUE);
  updateChangesLog(log, true);
  changeLock(CLOSED_VALUE);
  updateUserleds(log);
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

static void commandShowCurrentLog(const log_t* logc){
  char stri [100] = "start of message:\r\n";
  char strf [100] = "end of message.\r\n";
  pcSerialComStringWrite( stri );
  commandShowCurrentLockState(logc);
  commandShowCurrentButtonsState(logc);
  commandShowCurrentLedsState(logc);
  commandShowCurrentTemp(logc);
  commandShowCurrentHum(logc);
  commandShowCurrentSens(logc);
  commandShowDateAndTime();
  pcSerialComStringWrite(strf);
  return;
}
