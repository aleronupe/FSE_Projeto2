#include "structuresCentral.h"

void inicializa_dados(Servidor_Struct *servStruct) {
    servStruct->flag_run = 1;
    servStruct->lamp1 = 0;
    servStruct->lamp2 = 0;
    servStruct->lamp3 = 0;
    servStruct->lamp4 = 0;
    servStruct->ar1 = 0;
    servStruct->ar2 = 0;
    // ---------------
    servStruct->alarme = 0;
    servStruct->sinalAlarme = 0;
    // ----------------
    servStruct->temp = 00.00;
    servStruct->hum = 00.00;
    // ----------------
    servStruct->sensorPres1 = 0;
    servStruct->sensorPres2 = 0;
    servStruct->sensorAbrt1 = 0;
    servStruct->sensorAbrt2 = 0;
    servStruct->sensorAbrt3 = 0;
    servStruct->sensorAbrt4 = 0;
    servStruct->sensorAbrt5 = 0;
    servStruct->sensorAbrt6 = 0;
    servStruct->tipo_mensagem = 1;
}