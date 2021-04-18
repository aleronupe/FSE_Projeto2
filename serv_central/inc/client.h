#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structures.h"

void envia_mensagem_distribuido(char cod_sinal, int estado_sinal, char pos);

void monta_cliente();

void fecha_cliente();