#ifndef HTTP_h
#define HTTP_h
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "WiFiService.h"
#include "Config.h"

class HTTP{
    public:
        HTTP();
        String request(String, String, String) const;
};

#endif
