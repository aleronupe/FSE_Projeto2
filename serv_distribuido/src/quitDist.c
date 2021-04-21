#include "quitDist.h"

pthread_t *local_server_tid;
Servidor_Struct *local_main_struct;

void handle_quit(pthread_t *server_tid, Servidor_Struct *main_struct) {
    local_server_tid = server_tid;
    local_main_struct = main_struct;
}

void mata_threads() {
    envia_mensagem_central('E', 'E', 0);
    sleep(1);
    local_main_struct->flag_run = 0;
    fecha_conexoes();
    sleep(1);
    fecha_conexoes_TCP();
    sleep(1);
    fecha_cliente();
    pthread_cancel(*local_server_tid);
    exit(0);
}

void mata_threads_sem_chamar() {
    sleep(1);
    local_main_struct->flag_run = 0;
    fecha_conexoes();
    sleep(1);
    fecha_conexoes_TCP();
    sleep(1);
    fecha_cliente();
    pthread_cancel(*local_server_tid);
    exit(0);
}
