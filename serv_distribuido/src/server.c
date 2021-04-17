#include "server.h"

int servidorSocket;
int socketCliente;

void TrataClienteTCP(int socketCliente, Servidor_Struct *servStruct) {
    char buffer[15];
    char envio[30] = {"1Menino, não é que veio?1"};
    int tamanhoRecebido;

    memset(buffer, '\0', sizeof(buffer));

    if ((tamanhoRecebido = recv(socketCliente, buffer, 15, 0)) < 0)
        printf("Erro no recv1()\n");

    printf("o que recebeu foi:\n");
    printf("%s\n", buffer);

    if (strcmp(buffer, "LIGA01") == 0) {
        servStruct->lamp1 = servStruct->lamp1 ? 0 : 1;
        liga_desliga_lamp_1(servStruct->lamp1);

    } else if (strcmp(buffer, "LIGA02") == 0) {
        servStruct->lamp2 = servStruct->lamp2 ? 0 : 1;
        liga_desliga_lamp_2(servStruct->lamp2);

    } else if (strcmp(buffer, "LIGA03") == 0) {
        servStruct->lamp3 = servStruct->lamp3 ? 0 : 1;
        liga_desliga_lamp_3(servStruct->lamp3);

    } else if (strcmp(buffer, "LIGA03") == 0) {
        servStruct->lamp3 = servStruct->lamp3 ? 0 : 1;
        liga_desliga_lamp_3(servStruct->lamp3);

    } else if (strcmp(buffer, "LIGA04") == 0) {
        servStruct->lamp4 = servStruct->lamp4 ? 0 : 1;
        liga_desliga_lamp_4(servStruct->lamp4);

    } else if (strcmp(buffer, "AR01") == 0) {
        servStruct->ar1 = servStruct->ar1 ? 0 : 1;
        liga_desliga_ar_1(servStruct->ar1);

    } else if (strcmp(buffer, "AR02") == 0) {
        servStruct->ar2 = servStruct->ar2 ? 0 : 1;
        liga_desliga_ar_2(servStruct->ar2);
    }

    // while (tamanhoRecebido > 0) {
    //     if (send(socketCliente, envio, 30, 0) != 30)
    //         printf("Erro no envio - send()\n");

    //     if ((tamanhoRecebido = recv(socketCliente, buffer, 15, 0)) < 0)
    //         printf("Erro no recv2()\n");
    // }
}

void monta_servidor(void *args) {
    Servidor_Struct *servStruct = (Servidor_Struct *)args;
    struct sockaddr_in servidorAddr;
    struct sockaddr_in clienteAddr;
    unsigned short servidorPorta;
    unsigned int clienteLength;

    servidorPorta = SERV_PORT;

    // Abrir Socket
    if ((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("falha no socker do Servidor\n");

    // Montar a estrutura sockaddr_in
    memset(&servidorAddr, 0,
           sizeof(servidorAddr));  // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servidorAddr.sin_port = htons(servidorPorta);

    // Bind
    if (bind(servidorSocket, (struct sockaddr *)&servidorAddr,
             sizeof(servidorAddr)) < 0)
        printf("Falha no Bind\n");

    // Listen
    if (listen(servidorSocket, 10) < 0) printf("Falha no Listen\n");

    int conexaoEstabelecida = 0;

    while (!conexaoEstabelecida && servStruct->flag_run) {
        clienteLength = sizeof(clienteAddr);
        if ((socketCliente =
                 accept(servidorSocket, (struct sockaddr *)&clienteAddr,
                        &clienteLength)) < 0)
            printf("Falha no Accept\n");
        else {
            printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
            conexaoEstabelecida = 1;
        }

        TrataClienteTCP(socketCliente, servStruct);
        close(socketCliente);
    }
    close(servidorSocket);
}

void fecha_conexoes_TCP() {
    close(socketCliente);
    close(servidorSocket);
}