#ifndef ALARM_H_
#define ALARM_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "structures.h"

void define_alarme(Servidor_Struct *servStruct, pthread_t *alarm_tid);

#endif /* ALARM_H_ */
