#ifndef STRUCUTRES_H_
#define STRUCUTRES_H_

typedef struct servidor_struct
{
    int flag_run;
    int lamp1, lamp2, lamp3, lamp4;
    int ar1, ar2;
    int sensorPres1, sensorPres2;
    int sensorAbrt1, sensorAbrt2, sensorAbrt3;
    int sensorAbrt4, sensorAbrt5, sensorAbrt6;
    int alarme, sinalAlarme;
    float temp, hum;
    char mensagem[100];
    char tipo_mensagem;

} Servidor_Struct;

#endif /* STRUCUTRES_H_ */
