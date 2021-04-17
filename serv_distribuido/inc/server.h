#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"
#include "gpio.h"

#define SERV_PORT 10110

void monta_servidor(void *args);

void fecha_conexoes();