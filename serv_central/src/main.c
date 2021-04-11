#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "painel.h"
#include "structures.h"

Servidor_Struct servStruct;

void mata_threads() {
    printf("Matou o processo\n");
    servStruct.flag_run = 0;
    sleep(2);
    desliga_telas();
    exit(0);
}

int main(int argc, const char *argv[]) {
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);

    servStruct.flag_run = 1;
    servStruct.lamp1 = 0;
    servStruct.lamp2 = 0;
    servStruct.lamp3 = 0;
    servStruct.lamp4 = 0;
    servStruct.ar1 = 0;
    servStruct.ar2 = 0;
    // ---------------
    servStruct.alarme = 0;
    servStruct.sinalAlarme = 0;
    // ----------------
    servStruct.temp = 20.00;
    servStruct.hum = 10.00;
    // ----------------
    servStruct.sensorPres1 = 0;
    servStruct.sensorPres2 = 0;
    servStruct.sensorAbrt1 = 0;
    servStruct.sensorAbrt2 = 0;
    servStruct.sensorAbrt3 = 0;
    servStruct.sensorAbrt4 = 0;
    servStruct.sensorAbrt5 = 0;
    servStruct.sensorAbrt6 = 0;

    iniciaTela();

    pthread_t menu_tid;

    pthread_create(&menu_tid, NULL, (void *)carregaMenu, (void *)&servStruct);

    int alter = 1;

    while (servStruct.flag_run == 1) {
        sleep(2);
        if (alter == 1) {
            servStruct.lamp1 = 1;
            servStruct.lamp2 = 1;
            servStruct.lamp3 = 1;
            servStruct.lamp4 = 1;
            servStruct.ar1 = 0;
            servStruct.ar2 = 0;
            // ----------
            servStruct.alarme = 0;
            servStruct.sinalAlarme = 1;
            // ----------
            servStruct.temp = 20.00;
            servStruct.hum = 10.00;
            // ----------
            servStruct.sensorPres1 = 0;
            servStruct.sensorPres2 = 0;
            servStruct.sensorAbrt1 = 1;
            servStruct.sensorAbrt2 = 1;
            servStruct.sensorAbrt3 = 1;
            servStruct.sensorAbrt4 = 1;
            servStruct.sensorAbrt5 = 1;
            servStruct.sensorAbrt6 = 1;
        } else {
            servStruct.lamp1 = 0;
            servStruct.lamp2 = 0;
            servStruct.lamp3 = 0;
            servStruct.lamp4 = 0;
            servStruct.ar1 = 1;
            servStruct.ar2 = 1;
            // ----------
            servStruct.alarme = 1;
            servStruct.sinalAlarme = 0;
            // ----------
            servStruct.temp = 10.00;
            servStruct.hum = 20.00;
            // ----------
            servStruct.sensorPres1 = 1;
            servStruct.sensorPres2 = 1;
            servStruct.sensorAbrt1 = 0;
            servStruct.sensorAbrt2 = 0;
            servStruct.sensorAbrt3 = 0;
            servStruct.sensorAbrt4 = 0;
            servStruct.sensorAbrt5 = 0;
            servStruct.sensorAbrt6 = 0;
        }
        alter = alter * (-1);
    }

    pthread_join(menu_tid, NULL);

    return 0;
}
