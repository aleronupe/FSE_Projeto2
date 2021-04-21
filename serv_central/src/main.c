#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "alarm.h"
#include "clientCentral.h"
#include "csv.h"
#include "painel.h"
#include "quit.h"
#include "serverCentral.h"
#include "structuresCentral.h"

Servidor_Struct servStruct;
pthread_t menu_tid;
pthread_t server_tid;
pthread_t alarm_tid;

int main(int argc, const char *argv[]) {
    handle_quit(&menu_tid, &server_tid, &alarm_tid, &servStruct);

    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);
    signal(SIGPIPE, SIG_IGN);

    inicializa_dados(&servStruct);

    iniciaTela();
    monta_cliente();

    pthread_create(&menu_tid, NULL, (void *)carregaMenu, (void *)&servStruct);
    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&servStruct);

    // pthread_detach(menu_tid);
    // pthread_detach(server_tid);

    abre_ou_cria_csv();

    define_alarme(&servStruct, &alarm_tid);

    while (servStruct.flag_run == 1) {
        requisita_temperatura(&servStruct);
        usleep(500000);
    }

    pthread_join(menu_tid, NULL);
    pthread_join(server_tid, NULL);

    mata_threads();
    return 0;
}
