//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include "tempsensor.h"
#include "eventlog.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static void sendStartSignal(dht11_t* sensor);
static bool waitForResponse(dht11_t* sensor);
static bool readBit(dht11_t* sensor);
static uint8_t readByte(dht11_t* sensor);
static bool dht11Read(dht11_t* sensor);
static int getSensorTemp(dht11_t* sensor);
static int getSensorHum(dht11_t* sensor);
//=====[Implementations of public functions]===================================

void initSensor(dht11_t* sensor, PinName pin) {
  sensor->pin = pin;
  sensor->data = new DigitalInOut(pin);
  sensor->temperature = 0;
  sensor->humidity = 0;
  return;
}

void updateSensor(log_t* sensorlog, dht11_t* sensor1){

  if(false == dht11Read(sensor1)){
    return;
  }


  updateTempLog(sensorlog, getSensorTemp(sensor1));
  updateHumLog(sensorlog, getSensorHum(sensor1));
  
  return;
    
}

//=====[Implementations of private functions]==================================

static void sendStartSignal(dht11_t* sensor){
  sensor->data->output();
  sensor->data->write(0);
  wait_us(18000); 
  sensor->data->write(1);
  wait_us(30);  
  sensor->data->input();
  return;
}


static bool waitForResponse(dht11_t* sensor){
  
  int count = 0;

  while (sensor->data->read() == 1){
    wait_us(1);
    if (++count > 100) return false;
  }

  count = 0;
  while (sensor->data->read() == 0){
    wait_us(1);
    if (++count > 100) return false;
  }

  count = 0;
  while (sensor->data->read() == 1){
    wait_us(1);
    if (++count > 100) return false;
  }

  return true;
}


static bool readBit(dht11_t* sensor){
  int count = 0;
  while (sensor->data->read() == 0){
    wait_us(1);
    if (++count > 100) return false;
  }

  wait_us(40); 
  return sensor->data->read() == 1;
}


static uint8_t readByte(dht11_t* sensor){
  uint8_t result = 0;
  for (int i = 0; i < 8; i++){
    result <<= 1;
    if (readBit(sensor)) result |= 1;
  }
  return result;
}

static bool dht11Read(dht11_t* sensor){
  
  uint8_t data[5];

  sendStartSignal(sensor);
  if (!waitForResponse(sensor)) return false;

  for (int i = 0; i < 5; i++){
    data[i] = readByte(sensor);
  }

  uint8_t checksum = data[0] + data[1] + data[2] + data[3];
  if (checksum != data[4]) return false;

  sensor->humidity = (int) data[0];
  sensor->temperature = (int) data[2];


  return true;
}

static int getSensorTemp(dht11_t* sensor){
  return sensor->temperature;
}

static int getSensorHum(dht11_t* sensor){
  return sensor->humidity;
}

