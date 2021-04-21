#ifndef SERVER_CENTRAL_H_
#define SERVER_CENTRAL_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structuresCentral.h"

#define SERV_PORT 10010

void *monta_servidor(void *args);

void fecha_conexoes_TCP();

#endif /* SERVER_CENTRAL_H_ */