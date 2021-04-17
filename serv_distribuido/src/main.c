#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "control.h"
#include "structures.h"
#include "client.h"
#include "server.h"

Servidor_Struct main_struct;

void mata_threads() { main_struct.flag_run = 0; }

int main(int argc, const char *argv[]) {
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);

    main_struct.flag_run = 1;
    // --------Entradas--------
    main_struct.lamp1 = 0;
    main_struct.lamp2 = 0;
    main_struct.lamp3 = 0;
    main_struct.lamp4 = 0;
    main_struct.ar1 = 0;
    main_struct.ar2 = 0;
    // --------Alarme-------
    main_struct.alarme = 0;
    main_struct.sinalAlarme = 0;
    // ---------Sensores-------
    main_struct.sensorPres1 = 0;
    main_struct.sensorPres2 = 0;
    main_struct.sensorAbrt1 = 0;
    main_struct.sensorAbrt2 = 0;
    main_struct.sensorAbrt3 = 0;
    main_struct.sensorAbrt4 = 0;
    main_struct.sensorAbrt5 = 0;
    main_struct.sensorAbrt6 = 0;

    pthread_t control_tid;
    pthread_t server_tid;

    pthread_create(&control_tid, NULL, (void *)controle_temp,
                   (void *)&main_struct);
    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&main_struct);

    while (main_struct.flag_run == 1) {
        sleep(1);
    }

    pthread_join(control_tid, NULL);
    pthread_join(server_tid, NULL);


    return 0;
}
