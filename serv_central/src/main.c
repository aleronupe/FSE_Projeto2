#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "menu.h"

Arg_Struct main_struct;

void mata_threads()
{
    main_struct.flag_run = 0;
}

int main(int argc, const char *argv[])
{
    signal(SIGINT, mata_threads);
    signal(SIGKILL, mata_threads);

    iniciaTelas();

    opcoes_usuario(&main_struct);

    return 0;
}
