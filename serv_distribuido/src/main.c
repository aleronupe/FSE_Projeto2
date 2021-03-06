#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "clientDistribuido.h"
#include "control.h"
#include "gpio.h"
#include "serverDistribuido.h"
#include "structures.h"

Servidor_Struct main_struct;
// pthread_t server_tid;

void mata_threads() {
    main_struct.flag_run = 0;
    fecha_conexoes();
    sleep(1);
    fecha_conexoes_TCP();
    sleep(1);
    fecha_cliente();
    // pthread_cancel(server_tid);
    exit(0);
}

int main(int argc, const char *argv[]) {
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);
    signal(SIGPIPE, mata_threads);

    inicializa_dados(&main_struct);
    inicia_conexoes();
    monta_cliente();

    char mensagem_inicial[25];

    // pthread_create(&server_tid, NULL, (void *)monta_servidor,
    //                (void *)&main_struct);

    // pthread_detach(server_tid);

    memset(mensagem_inicial, '\0', sizeof(mensagem_inicial));
    read_sensors_init(mensagem_inicial);
    envia_mensagem_inicial(mensagem_inicial, &main_struct);

    // while (main_struct.flag_run == 1) {
    //     sleep(1);
    // }

    monta_servidor(&main_struct);

    mata_threads();

    return 0;
}
