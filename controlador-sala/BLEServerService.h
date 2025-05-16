#ifndef BLEServerService_h
#define BLEServerService_h
#include <Arduino.h>
#include <BLEDevice.h>
#ifdef _WIN32
    #include <Vector>
    #include <String>
#else
    #include <vector>
    #include <string>
#endif
#include <unordered_map>
#include "Hardware.h"
#include "Structs.h"
#include "AwaitHttpService.h"
#include "WiFiService.h"
#include "Config.h"


#define TIME_CONNECTION  5000 
#define TIME_WAITING_CONNECTION 180000

extern BLEUUID CHARACTERISTIC_UUID;
extern BLEUUID SERVICE_UUID;
class Hardware; // Resolver isso aqui. Dependencia Circular
// BleServerService >> Hardware >> Config >> UtilsService >> EnvironmentVariableService >> BLEServerService
 
class BLEServerService {
  public:
    static int __countTypeSensor;
    static int __countTypeActuator;
    static std::vector<String> __sensors;
    static std::vector<struct HardwareRecord> __actuators;
    static BLEScan* __pBLEScan;
    static std::vector<BLEAdvertisedDevice*> __filteredDevices;
    static std::unordered_map<std::string, Hardware> __devicesMapped;
    static BLEDeviceConnect* __actuatorConnected;
    static bool __receivedData;
    
    BLEServerService();
    
    static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify); 
    BLEDeviceConnect* connectToDevice(BLEAdvertisedDevice* myDevice, bool validateConnection); 
    void initBLE(); 
    void stopScan(); 
    void scanDevices(); 
    void populateMap(); 
    void activeBLEScan(); 
    bool isSensor(String uuid);
    bool isAtuador(String uuid);
    bool connectMyDisp(BLEAdvertisedDevice* device); 
    int getCountDispsTypeSensor();
    void timer(); 
    bool connectToActuator(String uuidDevice);
    void disconnectToActuator();
    void sendMessageToActuator(String data);

    // getters and setters
    std::vector<String> getSensors();
    std::vector<struct HardwareRecord> getActuators();
    void addSensor(String uuid);
    void addActuator(HardwareRecord act);
    void newCicle();
    
    static void setCountTypeSensor(int count);
    static void setCounttypeActuator(int count);
    static int getCountTypeSensor();
    static int getCounttypeActuator();

    void closeConnections(std::vector<BLEDeviceConnect*> aux);

    bool isSensorListed(String uuid, int typeDisp);

    // metods task
    void continuousConnectionTask();
    static void startTaskBLEImpl(void*);
    void startTaskBLE();
  
};

#endif
