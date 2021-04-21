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
#include "quitDist.h"

Servidor_Struct main_struct;
pthread_t server_tid;

int main(int argc, const char *argv[]) {
    handle_quit(&server_tid, &main_struct);

    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);
    signal(SIGPIPE, SIG_IGN);

    inicializa_dados(&main_struct);
    inicia_conexoes();
    monta_cliente();

    char mensagem_inicial[25];

    pthread_create(&server_tid, NULL, (void *)monta_servidor,
                   (void *)&main_struct);

    pthread_detach(server_tid);

    memset(mensagem_inicial, '\0', sizeof(mensagem_inicial));
    read_sensors_init(mensagem_inicial);
    int flag_done = 1;
    while (main_struct.flag_run) {
        if (flag_done) {
            envia_mensagem_inicial(mensagem_inicial, &main_struct, &flag_done);
        }
        sleep(1);
    }

    mata_threads();

    return 0;
}
