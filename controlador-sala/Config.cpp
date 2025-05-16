#include "Config.h"

String __url;
String __ssid;
String __password;
int    __ledStatus;
int    __basetime;
int    __type;
int    __route;
bool   __debug;
std::mutex Config::__bleActuatorMutex;
std::mutex Config::__envVariablesMutex;

Config config = Config::getInstance();

Config::Config(){
    __tokenApp  = "594ac3eb82b5080393ad5c426f61c1ed5ac53f90e1abebc15316888cf1c8f5fe";
    __url       = "http://itetech-001-site4.qtempurl.com/api";
    __debug     = true;
    //__ssid      = "TransmissaoAula";
    //__password  = "#ufstransmissao#";
    __ssid      = "AlumHuawei";
    __password  = "AF12301981";
    //__ssid      = "Apartamento 201-2.4";
    //__password  = "Ald50983021";
    __basetime  = 180000;
    __ledStatus = 2;
    __type  = TYPE_CONTROLLER;
    __route = 2;
    __wifiFailAttempts = 30;
    __commandSendAttempts = 3;
    __timesToHasOne = 3;
    
    pinMode(__ledStatus, OUTPUT);
}

String Config::getTokenApp(){ 
	return __tokenApp;
}

String Config::getUrl(){ 
	return __url;
}

void Config::setUrl(String url){
  __url = url;
}

String Config::getSSID(){
	return __ssid;
}

void setSSID(String ssid){
  __ssid = ssid;
}

String Config::getPassword(){
	return __password;
}

void setPassword(String password){
  __password = password;
}

int	Config::getBaseTime(){
	return __basetime;
}

int	Config::getType(){
	return __type;
}


void	Config::setType(int type){
	__type = type;
}

int	Config::getLedStatus() {
	return __ledStatus;
}

int Config::getRoute(){
    return __route;
}

int Config::getWifiFailAttempts(){
    return __wifiFailAttempts;
}

int Config::getCommandSendAttempts(){
    return __commandSendAttempts;
}

bool Config::isDebug() {
	return __debug;
}

int Config::getTimesToHasOne(){
  return __timesToHasOne;
}

void Config::lock() {
	__bleActuatorMutex.lock();
}

void Config::unlock(){
  __bleActuatorMutex.unlock();
}

void Config::lockEnvVariablesMutex() {
	__envVariablesMutex.lock();
}

void Config::unlockEnvVariablesMutex(){
  __envVariablesMutex.unlock();
}

Config& Config::getInstance(){
  static Config instance;
  return instance;
}

