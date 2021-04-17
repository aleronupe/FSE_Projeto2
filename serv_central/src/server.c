#include "server.h"

#include "structures.h"

int servidorSocket;
int socketCliente;

void TrataClienteTCP(int socketCliente) {
    char buffer[16];
    char envio[30] = {"Menino, não é que veio?"};
    int tamanhoRecebido;

    if ((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
        printf("Erro no recv1()\n");

    while (tamanhoRecebido > 0) {
        printf("Tamanho recebido: %d\n", tamanhoRecebido);

        if (send(socketCliente, envio, 30, 0) != 30)
            printf("Erro no envio - send()\n");

        if ((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
            printf("Erro no recv2()\n");
    }
}

// void envia_mensagem_distribuido(char num_lamp) {
//     char buffer[30];
//     char envio[30] = {"LIGA0"};
//     envio[5] = itoa(num_lamp);
//     int tamanhoRecebido;

//     if (send(socketCliente, envio, 30, 0) > 10)
//         printf("Erro no envio - send()\n");

//     if ((tamanhoRecebido = recv(socketCliente, buffer, 30, 0)) < 0)
//         printf("Erro no recv1()\n");

//     printf("%s\n", buffer);

//     while (tamanhoRecebido > 0) {
//         if ((tamanhoRecebido = recv(socketCliente, buffer, 30, 0)) < 0)
//             printf("Erro no recv2()\n");
//         printf("%s\n", buffer);
//     }
// }

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

        TrataClienteTCP(socketCliente);
        close(socketCliente);
    }
    close(servidorSocket);
}

void fecha_conexoes_TCP() {
    close(socketCliente);
    close(servidorSocket);
}