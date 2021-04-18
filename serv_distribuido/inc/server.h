#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"
#include "gpio.h"
#include "bme280.h"
#include "control.h"

#define SERV_PORT 10110

void monta_servidor(void *args);

void fecha_conexoes_TCP();

#endif /* SERVER_H_ */