#include "quit.h"

pthread_t *local_menu_tid;
pthread_t *local_server_tid;
pthread_t *local_alarm_tid;
Servidor_Struct *local_servStruct;

void handle_quit(pthread_t *menu_tid, pthread_t *server_tid,
                 pthread_t *alarm_tid, Servidor_Struct *servStruct) {
    local_menu_tid = menu_tid;
    local_server_tid = server_tid;
    local_alarm_tid = alarm_tid;
    local_servStruct = servStruct;
}

void mata_threads() {
    local_servStruct->tipo_mensagem = 9;
    local_servStruct->flag_run = 0;
    desliga_telas();
    fecha_conexoes_TCP();
    sleep(1);
    fecha_cliente();
    sleep(1);
    pthread_cancel(*local_menu_tid);
    pthread_cancel(*local_server_tid);
    pthread_cancel(*local_alarm_tid);
    exit(0);
}
