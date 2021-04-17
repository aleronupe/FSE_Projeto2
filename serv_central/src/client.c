#include "client.h"

int clienteSocket;
struct sockaddr_in servidorAddr;
unsigned short servidorPorta = 10110;
char IP_Servidor[15] = {"192.168.0.4"};

int bytesRecebidos;
int totalBytesRecebidos;
char buffer[30];
unsigned int tamanhoMensagem;

void envia_mensagem_distribuido(int num_lamp) {
    char mensagem[15];

    switch (num_lamp) {
        case 1:
            strcpy(mensagem, "LIGA01");
            break;
        case 2:
            strcpy(mensagem, "LIGA02");
            break;
    }
    printf("O Que eu ia enviar: %s\n", mensagem);

    // Construir struct sockaddr_in
    memset(&servidorAddr, 0,
           sizeof(servidorAddr));  // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);

    // Criar Socket
    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()\n");

    // Connect
    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    tamanhoMensagem = strlen(mensagem);

    if (send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf(
            "Erro no envio: numero de bytes enviados diferente do esperado\n");

    totalBytesRecebidos = 0;
    while (totalBytesRecebidos < tamanhoMensagem) {
        if ((bytesRecebidos = recv(clienteSocket, buffer, 30 - 1, 0)) <= 0)
            printf("Não recebeu o total de bytes enviados\n");
        totalBytesRecebidos += bytesRecebidos;
        buffer[bytesRecebidos] = '\0';
        printf("%s\n", buffer);
    }
    close(clienteSocket);
}