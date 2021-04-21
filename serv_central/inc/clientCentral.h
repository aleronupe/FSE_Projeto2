#ifndef CLIENT_CENTRAL_H_
#define CLIENT_CENTRAL_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structuresCentral.h"

void monta_cliente();

void envia_mensagem_distribuido(char cod_sinal, int estado_sinal, char pos);

void requisita_temperatura(Servidor_Struct *servStruct);

void fecha_cliente();

#endif /* CLIENT_CENTRAL_H_ */