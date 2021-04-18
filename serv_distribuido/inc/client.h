#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"

void monta_cliente();

void envia_mensagem_central(char cod_sinal, char pos, int estado_sinal);

void fecha_cliente();

#endif /* CLIENT_H_ */