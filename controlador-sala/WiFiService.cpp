#include "WiFiService.h"

WiFiService::WiFiService(){}

void WiFiService::connect(){   
    delay(4000);
    int attempt = 0;
    WiFi.begin(config.getSSID().c_str(), config.getPassword().c_str());
    while (WiFi.status() != WL_CONNECTED && attempt < config.getWifiFailAttempts()){
        digitalWrite(config.getLedStatus(), HIGH);
        delay(1000);
        digitalWrite(config.getLedStatus(), LOW); 
        attempt += 1;
        if (config.isDebug()){
            Serial.println(F("=================================="));
            Serial.println(F("[WiFiService] Conectando ao Wifi"));
            Serial.print(F("[WiFiService] Tentativa: ")); 
            Serial.println(attempt);
            Serial.print(F("[WiFiService] SSID: "));
            Serial.println(config.getSSID());
            Serial.print(F("[WiFiService] Password: " ));
            Serial.println(config.getPassword());
        }
    }

    if(WiFi.status() != WL_CONNECTED && attempt == config.getWifiFailAttempts()) {
      Serial.print(F("[WiFiService] Excedido o número de tentativas de conexão ao Wifi: "));
      Serial.println(config.getWifiFailAttempts());
      Serial.println(F("[WiFiService] Reiniciando ESP..."));
      ESP.restart();
    }

    digitalWrite(config.getLedStatus(), HIGH);
    
    if (WiFi.status() == WL_CONNECTED && config.isDebug())    {
        IPAddress ip = WiFi.localIP();
        Serial.println(F("=================================="));
        Serial.print(F("[WiFiService] Conectado a rede: "));
        Serial.println(config.getSSID());
        Serial.print("[WiFiService] Ip: ");
        Serial.println(ip);
    }
   
    return;
}

void WiFiService::disconnect()  {
    WiFi.disconnect();
    digitalWrite(config.getLedStatus(), LOW); 

    if (config.isDebug()){;
        Serial.println(F("=================================="));
        Serial.println(F("[WiFiService] Desconectado da rede: " ));
        Serial.println(config.getSSID());
    }
    
    return;
}
