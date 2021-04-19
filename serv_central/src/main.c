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

void mata_threads() {
    strcpy(servStruct.mensagem, "Matou o;processo; ");
    servStruct.tipo_mensagem = 5;
    servStruct.flag_run = 0;
    sleep(1);
    desliga_telas();
    fecha_conexoes_TCP();
    fecha_cliente();
    exit(0);
}

int main(int argc, const char *argv[]) {
    printf("Começou mesmo");
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
    strcpy(servStruct.mensagem, "Estado Inicial");
    servStruct.tipo_mensagem = 1;

    iniciaTela();
    monta_cliente();

    pthread_t menu_tid;
    pthread_t server_tid;

    // printf("Começou");

    pthread_create(&menu_tid, NULL, (void *)carregaMenu, (void
    *)&servStruct);
    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&servStruct);

    abre_ou_cria_csv();
    while (servStruct.flag_run == 1) {
        requisita_temperatura(&servStruct);
        usleep(800000);
        // sleep(1);
        // printf("servStruct.sensorPres1: %d\n", servStruct.sensorPres1);
        // printf("servStruct.sensorPres2: %d\n", servStruct.sensorPres2);
        // printf("servStruct.sensorAbrt1: %d\n", servStruct.sensorAbrt1);
        // printf("servStruct.sensorAbrt2: %d\n", servStruct.sensorAbrt2);
        // printf("servStruct.sensorAbrt3: %d\n", servStruct.sensorAbrt3);
        // printf("servStruct.sensorAbrt4: %d\n", servStruct.sensorAbrt4);
        // printf("servStruct.sensorAbrt5: %d\n", servStruct.sensorAbrt5);
        // printf("servStruct.sensorAbrt6: %d\n", servStruct.sensorAbrt6);
    }

    pthread_join(menu_tid, NULL);
    pthread_join(server_tid, NULL);

    mata_threads();

    return 0;
}
