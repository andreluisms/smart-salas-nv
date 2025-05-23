#include "AwaitHttpService.h"

// Config config = Config::getInstance();
BLEServerService* __bleConfiguration; 
HTTPService __httpService;
EnvironmentVariablesService __environment;
UtilsService __utils;
WiFiService __wifi;

AwaitHttpService::AwaitHttpService() {}

void AwaitHttpService::startAwait(){
    xTaskCreate(this->awaitSolicitation, "awaitSolicitation", 8192, this, 8, nullptr);
}

void AwaitHttpService::awaitSolicitation(void* _this){
    std::vector<Solicitacao> solicitacao;
    
    while(true){
        if(WiFi.status() == WL_CONNECTED){
            if (config.isDebug()){
                Serial.println("\n=======================================");
                Serial.println("[AwaitHttpService] Start");
            }

            solicitacao = __httpService.getSolicitacao(MONITORAMENTO);
            
            for (Solicitacao s : solicitacao)
                executeSolicitation(s);

            if (config.isDebug()){
                Serial.println("\n=======================================");
                Serial.println("[AwaitHttpService] End");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

bool AwaitHttpService::connectToActuator(String uuidDevice) {
  Serial.println("[AwaitHttpService]: connectToActuator ACTUATOR : " + uuidDevice);
  bool deviceConnected = false;
  int i = 0;
  int count = 8;
            
  do{ 
    i++;
    
    if (config.isDebug()){
      Serial.print("[AwaitHttpService]: attempt number: ");
      Serial.println(i);
    }
    
    deviceConnected = __bleConfiguration->connectToActuator(uuidDevice);
    
    if(deviceConnected)
      break;

    delay(2000);

  } while(i < count);

  if( i >= count && !deviceConnected)
      Serial.println("[AwaitHttpService]: device not found");

  return deviceConnected;
}

void AwaitHttpService::executeSolicitation(Solicitacao request) 
{
    config.lock();

    if(!__bleConfiguration->isSensorListed(request.uuid, TYPE_ACTUATOR)) {
        
        __httpService.putSolicitacao(request.id);
        
        return; 
    }

    HTTP_REQUEST = true;

    vTaskDelay(1500/portTICK_PERIOD_MS);
    
    bool dispConnected = connectToActuator(request.uuid);

    if(dispConnected){
        String payload = getMessageToSend(request);
        Serial.println("==================================");
        Serial.println("[AwaitHttpService] Sendig Payload: " + payload);

        std::vector<String> subStrings = __utils.splitPayload(payload, MAX_LENGTH_PACKET);

        // String packet;
        for (String packet : subStrings){
            Serial.println("==================================");         
            Serial.println("[AwaitHttpService] Sendig packet: " + packet);
            __bleConfiguration->sendMessageToActuator(packet);
        }

        awaitsReturn();
    }

    __bleConfiguration->disconnectToActuator();
    
    HTTP_REQUEST = false;
    
    delay(2000);

    __utils.updateMonitoring(HTTP_MESSAGE);

    __httpService.putSolicitacao(request.id);

    if (config.isDebug()){
        Serial.println("==================================");
        Serial.println("[AwaitHttpService] Resposta BLE");
        Serial.println("[AwaitHttpService] recebeu retorno: " + HTTP_RECEIVED_DATA);
        Serial.println("[AwaitHttpService] mensagem: " + HTTP_MESSAGE);
    }

    HTTP_RECEIVED_DATA = false;
    HTTP_MESSAGE = "";  

    config.unlock();
}

String AwaitHttpService::getMessageToSend(Solicitacao request)
{
    String typeEquipament = "", state = "", command = "null";

    if(request.type == LUZES)
        typeEquipament = "LZ";
    else{
        typeEquipament = "AC";
        command = request.code;
    }

    if(request.acting == "True")
        state = "ON";
    else
        state = "OFF";

    return __utils.mountPayload(typeEquipament, state, command);
}

void AwaitHttpService::awaitsReturn()
{
  unsigned long tempoLimite = millis() + 15000;
  while(millis() <= tempoLimite && !HTTP_RECEIVED_DATA){ 
      delay(1000);
      if (config.isDebug()){    
        Serial.print("[AwaitHttpService] TIME AWAITS: ");
        Serial.println(millis());
      }
  }    
}