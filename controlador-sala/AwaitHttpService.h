#ifndef AwaitHttpService_h
#define AwaitHttpService_h


#ifdef _WIN32
    #include <Vector>
#else
    #include <vector>
#endif
#include <Arduino.h>
#include "Structs.h"
#include "BLEServerService.h"
#include "HTTPService.h"
#include "EnvironmentVariablesService.h"
#include "UtilsService.h"
#include "WiFiService.h"
#include "Config.h"

#define CONDICIONADOR  "AR_CONDICIONADO"
#define LUZES "LUZES"
#define MONITORAMENTO "MONITORAMENTO"
#define ATUALIZAR "ATUALIZAR_HORARIOS"

class AwaitHttpService {
  private: 
    static void awaitsReturn();
    static String getMessageToSend(Solicitacao request);
    static MonitoringRequest deserealizeObject(String payload);

  public: 
    AwaitHttpService();

    static void awaitSolicitation(void* _this);
    static void executeSolicitation(Solicitacao solicitacao); 

    // Solicitacao
    void startAwait();
    static bool connectToActuator(String uuidDevice); 

};

#endif
