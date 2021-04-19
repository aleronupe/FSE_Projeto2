#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "clientCentral.h"
#include "csv.h"
#include "painel.h"
#include "serverCentral.h"
#include "structures.h"

Servidor_Struct servStruct;
pthread_t menu_tid;
pthread_t server_tid;

void mata_threads() {
    servStruct.tipo_mensagem = 9;
    servStruct.flag_run = 0;
    sleep(1);
    desliga_telas();
    fecha_conexoes_TCP();
    fecha_cliente();
    pthread_cancel(menu_tid);
    pthread_cancel(server_tid);
    exit(0);
}

int main(int argc, const char *argv[]) {
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);
    signal(SIGPIPE, mata_threads);

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
    servStruct.tipo_mensagem = 1;

    iniciaTela();
    monta_cliente();

    pthread_create(&menu_tid, NULL, (void *)carregaMenu, (void *)&servStruct);
    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&servStruct);

    pthread_detach(menu_tid);
    pthread_detach(server_tid);

    abre_ou_cria_csv();
    while (servStruct.flag_run == 1) {
        requisita_temperatura(&servStruct);
        usleep(500000);
    }

    mata_threads();

    return 0;
}
