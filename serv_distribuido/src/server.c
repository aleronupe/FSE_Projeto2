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

    switch (buffer[0]) {
        case 'L':
            switch (buffer[2]) {
                case '1':
                    servStruct->lamp1 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_lamp_1(servStruct->lamp1);
                    break;
                case '2':
                    servStruct->lamp2 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_lamp_2(servStruct->lamp2);
                    break;
                case '3':
                    servStruct->lamp3 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_lamp_3(servStruct->lamp3);
                    break;
                case '4':
                    servStruct->lamp4 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_lamp_4(servStruct->lamp4);
                    break;
            }
            break;
        case 'A':
            switch (buffer[2]) {
                case '1':
                    servStruct->ar1 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_ar_1(servStruct->ar1);
                    break;
                case '2':
                    servStruct->ar2 = buffer[0] == '1' ? 1 : 0;
                    liga_desliga_ar_2(servStruct->ar2);
                    break;
            }
            break;
    }

    if (send(socketCliente, envio, 30, 0) != 30)
        printf("Erro no envio - send()\n");

    printf("Finaliza recepção de dados do cliente\n");

    // while (tamanhoRecebido > 0) {
    //     if (send(socketCliente, envio, 30, 0) != 30)
    //         printf("Erro no envio - send()\n");

    //     // if ((tamanhoRecebido = recv(socketCliente, buffer, 15, 0)) < 0)
    //     //     printf("Erro no recv2()\n");
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
    if (listen(servidorSocket, 1) < 0) printf("Falha no Listen\n");

    // int conexaoEstabelecida = 0;

    while (servStruct->flag_run) {
        clienteLength = sizeof(clienteAddr);
        printf("Prepara para aceitar cliente\n");
        if ((socketCliente =
                 accept(servidorSocket, (struct sockaddr *)&clienteAddr,
                        &clienteLength)) < 0)
            printf("Falha no Accept\n");
        else {
            printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
            // conexaoEstabelecida = 1;
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