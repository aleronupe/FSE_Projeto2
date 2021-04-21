#ifndef QUIT_DIST_H_
#define QUIT_DIST_H_

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "clientDistribuido.h"
#include "gpio.h"
#include "serverDistribuido.h"
#include "structures.h"

void handle_quit(pthread_t *server_tid, Servidor_Struct *main_struct);

void mata_threads();

void mata_threads_sem_chamar();

#endif /* QUIT_DIST_H_ */