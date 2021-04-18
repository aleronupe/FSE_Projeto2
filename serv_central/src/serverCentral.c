#include "serverCentral.h"

int servidorSocket;
int socketCliente;

void TrataClienteTCP(int socketCliente, Servidor_Struct *servStruct) {
    char buffer[15];
    char envio[30] = {"1Menino, não é que veio?1"};
    int tamanhoRecebido;

    memset(buffer, '\0', sizeof(buffer));

    if ((tamanhoRecebido = recv(socketCliente, buffer, 15, 0)) < 0)
        printf("Erro no recv1()\n");

    switch (buffer[0]) {
        case 'P':
            switch (buffer[1]) {
                case '1':
                    servStruct->sensorPres1 = buffer[2];
                    break;
                case '2':
                    servStruct->sensorPres2 = buffer[2];
                    break;
            }
            break;
        case 'A':
            switch (buffer[1]) {
                case '1':
                    servStruct->sensorAbrt1 = buffer[2];
                    break;
                case '2':
                    servStruct->sensorAbrt2 = buffer[2];
                    break;
                case '3':
                    servStruct->sensorAbrt3 = buffer[2];
                    break;
                case '4':
                    servStruct->sensorAbrt4 = buffer[2];
                    break;
                case '5':
                    servStruct->sensorAbrt5 = buffer[2];
                    break;
                case '6':
                    servStruct->sensorAbrt6 = buffer[2];
                    break;
            }
            break;
    }

    if (send(socketCliente, envio, 30, 0) != 30)
        printf("Erro no envio - send()\n");

    // printf("Finaliza recepção de dados do cliente\n");
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

    while (servStruct->flag_run) {
        clienteLength = sizeof(clienteAddr);
        // printf("Pronto para Aceitar cliente\n");
        strcpy(servStruct->mensagem, "Pronto para;Aceitar cliente;");
        servStruct->tipo_mensagem = 5;
        if ((socketCliente =
                 accept(servidorSocket, (struct sockaddr *)&clienteAddr,
                        &clienteLength)) < 0) {
            printf("Falha no Accept\n");
            strcpy(servStruct->mensagem, "Falha no;Accept");
            servStruct->tipo_mensagem = 5;
        } else {
            // printf("Conexão estabelecida\n");
            char aviso[40];
            sprintf(aviso, "Conexão do ;Cliente;%s",
                    inet_ntoa(clienteAddr.sin_addr));
            strcpy(servStruct->mensagem, aviso);
            servStruct->tipo_mensagem = 1;
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
