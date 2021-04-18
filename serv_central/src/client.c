#include "client.h"

int clienteSocket;
struct sockaddr_in servidorAddr;
unsigned short servidorPorta = 10110;
char IP_Servidor[15] = {"192.168.0.52"};

int bytesRecebidos;
char buffer[30];
unsigned int tamanhoMensagem;

void monta_cliente() {
    // Construir struct sockaddr_in
    memset(&servidorAddr, 0,
           sizeof(servidorAddr));  // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    // Criar Socket
    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()\n");
}

void envia_mensagem_distribuido(int num_lamp) {
    char mensagem[15];

    memset(mensagem, '\0', sizeof(mensagem));

    switch (num_lamp) {
        case 1:
            strcpy(mensagem, "LIGA01");
            break;
        case 2:
            strcpy(mensagem, "LIGA02");
            break;
        case 3:
            strcpy(mensagem, "LIGA03");
            break;
        case 4:
            strcpy(mensagem, "LIGA04");
            break;
        case 5:
            strcpy(mensagem, "AR01");
            break;
        case 6:
            strcpy(mensagem, "AR01");
            break;
    }
    printf("O Que eu ia enviar: %s\n", mensagem);

    tamanhoMensagem = strlen(mensagem);

    // Connect
    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    if (send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf(
            "Erro no envio: numero de bytes enviados diferente do esperado\n");

    char sinalRecebido = '0';

    while (sinalRecebido != '1') {
        bzero(buffer, 30);
        recv(clienteSocket, buffer, 30, 0);
        if (buffer[1] != '1') printf("Não recebeu o total de bytes enviados\n");
        sinalRecebido = buffer[0];
        printf("[%s]\n", buffer);
        sleep(2);
    }
    close(clienteSocket);
}

void fecha_cliente() { close(clienteSocket); }