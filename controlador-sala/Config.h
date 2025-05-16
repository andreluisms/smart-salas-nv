
#ifndef Config_h
#define Config_h

#include <Arduino.h>
#include <mutex>
#include "UtilsService.h"

class Config
{
    private :
        String __tokenApp;
        String __url;
        String __ssid;
        String __password;
        int    __ledStatus;
        int    __basetime;
        bool   __debug;
        int    __type;
        int    __route;
        int    __wifiFailAttempts;
        int    __commandSendAttempts;
        int    __timesToHasOne;
        static std::mutex __bleActuatorMutex;
        static std::mutex __envVariablesMutex;

    public : 
        
        String getTokenApp();
        String getUrl();
        void setUrl(String url);
        String getSSID();
        void setSSID(String ssid);
        String getPassword();
        void setPassword(String password);
        int    getType();
        void    setType(int type);
        int    getBaseTime();
        int    getLedStatus();
        bool   isDebug();
        int    getRoute();        
        int    getWifiFailAttempts();
        int    getCommandSendAttempts();
        int    getTimesToHasOne();
        void   lock();
        void   unlock();
        void   lockEnvVariablesMutex();
        void   unlockEnvVariablesMutex();
        static Config& getInstance();
};

extern Config config;

#endif
