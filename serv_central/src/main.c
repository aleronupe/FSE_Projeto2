#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cJSON.h"
#include "client.h"
#include "painel.h"
#include "server.h"
#include "structures.h"

Servidor_Struct servStruct;

void mata_threads() {
    printf("Matou o processo\n");
    servStruct.flag_run = 0;
    sleep(1);
    // desliga_telas();
    // fecha_conexoes_TCP();
    fecha_cliente();
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

    // iniciaTela();
    monta_cliente();

    // pthread_t menu_tid;
    // pthread_t server_tid;

    // pthread_create(&menu_tid, NULL, (void *)carregaMenu, (void *)&servStruct);
    // pthread_create(&server_tid, NULL, (void *)monta_servidor, (void *)&servStruct);
    
    while (servStruct.flag_run == 1) {
        envia_mensagem_distribuido(1);
        sleep(10);
        envia_mensagem_distribuido(2);
        sleep(10);
        envia_mensagem_distribuido(3);
        sleep(10);
        envia_mensagem_distribuido(4);
        sleep(10);
        envia_mensagem_distribuido(5);
        sleep(10);
        envia_mensagem_distribuido(6);
    }

    // pthread_join(menu_tid, NULL);
    // pthread_join(server_tid, NULL);

    mata_threads();

    return 0;
}
