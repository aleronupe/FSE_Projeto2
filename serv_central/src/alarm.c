#include "alarm.h"

void alarm_handler(void *args) {
    Servidor_Struct *servStruct = (Servidor_Struct *)args;
    while (servStruct->flag_run) {
        if (servStruct->sinalAlarme) {
            system("cd ..; omxplayer alert.mp3 > /dev/null");
        }
        sleep(1);
    }
}

void define_alarme(Servidor_Struct *servStruct, pthread_t *alarm_tid) {
    pthread_create(alarm_tid, NULL, (void *)alarm_handler, (void *)servStruct);
    pthread_detach(*alarm_tid);
}
