#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "control.h"
#include "structures.h"

Servidor_Struct main_struct;

void mata_threads()
{
    main_struct.flag_run = 0;
}

int main(int argc, const char *argv[])
{
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);

    main_struct.flag_run = 1;

    pthread_t control_tid;

    pthread_create(&control_tid, NULL, (void *)controle_temp, (void *)&main_struct);

    while(main_struct.flag_run == 1){
        sleep(1);
    }

    pthread_join(control_tid, NULL);

    return 0;
}
