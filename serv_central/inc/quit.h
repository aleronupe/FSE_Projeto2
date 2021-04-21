#ifndef QUIT_H_
#define QUIT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "structuresCentral.h"

#include "alarm.h"
#include "clientCentral.h"
#include "painel.h"
#include "serverCentral.h"
#include "structuresCentral.h"

void handle_quit(pthread_t *menu_tid, pthread_t *server_tid,
                 pthread_t *alarm_tid, Servidor_Struct *servStruct);

void mata_threads();

void mata_threads_sem_chamar();

#endif /* QUIT_H_ */