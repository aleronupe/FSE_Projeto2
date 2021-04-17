#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"

void envia_mensagem_distribuido(int num_lamp);

void monta_cliente();

void fecha_cliente();