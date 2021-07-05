#ifndef CLIENT_DISTRIBUIDO_H_
#define CLIENT_DISTRIBUIDO_H_

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "structures.h"

void monta_cliente();

void envia_mensagem_central(char cod_sinal, char pos, int estado_sinal);

void *envia_mensagem_inicial(char *initial_message, Servidor_Struct *servStruct, int *flag_done);

void fecha_cliente();

#endif /* CLIENT_DISTRIBUIDO_H_ */