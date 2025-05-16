#ifndef WiFiService_h
#define WiFiService_h

#include <Arduino.h>
#include <WiFi.h>
#include "Config.h"

// #define WIFISERVICE F("[WiFiService]") // Testar para avaliar economia.

class WiFiService{
    public:
        WiFiService();
        void   connect();
        void   disconnect();
};

#endif
