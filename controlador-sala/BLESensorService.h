#ifndef BLESensorService_h
#define BLESensorService_h

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "Enums.h"
#include "EnvironmentVariablesService.h"
#include "Global.h"
#include "Hardware.h"
#include "EquipmentService.h"

// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>
// 
// #include <Arduino.h>
// #include "EquipmentService.h"

// #ifdef _WIN32
//     #include <String> // Para Windows
//     #include <Vector>
// #else
//     #include <string> // Para Linux
//     #include <vector>
// #endif


#define CHARACTERISTICUUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define SERVICEUUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define GET_DATA  "GET_DATA"
#define END_DATA  "END_DATA"
#define LED 2


extern BLECharacteristic* pCharacteristicSensor;
extern bool deviceConnected;
extern BLEServer* pServer;
extern EnvironmentVariablesService __environmentVariableService;
extern DeviceType deviceType;
extern EquipmentService equipmentService;
extern String equipmentState;
extern String receivedData;

void sendDataToServer(String data);

class MyServerCallbacks:public BLEServerCallbacks {
  public:
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
};


class MyCallbacks: public BLECharacteristicCallbacks {
  public: 
    void onWrite(BLECharacteristic * pCharacteristic);
};

void initBLEClient(String deviceName, DeviceType devType);
#endif
