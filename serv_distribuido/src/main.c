#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "client.h"
#include "control.h"
#include "server.h"
#include "structures.h"

Servidor_Struct main_struct;
pthread_t server_tid;

void mata_threads() {
    main_struct.flag_run = 0;
    fecha_conexoes();
    sleep(1);
    fecha_conexoes_TCP();
    sleep(1);
    fecha_cliente();
    pthread_cancel(server_tid);
}

int main(int argc, const char *argv[]) {
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);
    signal(SIGPIPE, NULL);


    inicializa_dados(&main_struct);
    inicia_conexoes();

    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&main_struct);

    pthread_detach(server_tid);

    while (main_struct.flag_run == 1) {
        sleep(1);
    }

    return 0;
}
