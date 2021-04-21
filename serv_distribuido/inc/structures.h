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
    int conectado;

} Servidor_Struct;

void inicializa_dados(Servidor_Struct *main_struct);

#endif /* STRUCUTRES_H_ */
