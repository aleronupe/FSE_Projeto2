#include "structures.h"

void inicializa_dados(Servidor_Struct *main_struct){
    main_struct->flag_run = 1;
    // --------Entradas--------
    main_struct->lamp1 = 0;
    main_struct->lamp2 = 0;
    main_struct->lamp3 = 0;
    main_struct->lamp4 = 0;
    main_struct->ar1 = 0;
    main_struct->ar2 = 0;
    // --------Alarme-------
    main_struct->alarme = 0;
    main_struct->sinalAlarme = 0;
    // ---------Sensores-------
    main_struct->sensorPres1 = 0;
    main_struct->sensorPres2 = 0;
    main_struct->sensorAbrt1 = 0;
    main_struct->sensorAbrt2 = 0;
    main_struct->sensorAbrt3 = 0;
    main_struct->sensorAbrt4 = 0;
    main_struct->sensorAbrt5 = 0;
    main_struct->sensorAbrt6 = 0;
}