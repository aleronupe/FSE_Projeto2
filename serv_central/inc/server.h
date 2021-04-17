#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERV_PORT 10010

void monta_servidor(void *args);

void fecha_conexoes();

void envia_mensagem_distribuido(char num_lamp);