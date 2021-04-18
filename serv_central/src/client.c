#include "client.h"

int clienteSocket;
int clienteTempSocket;
struct sockaddr_in servidorAddr;
unsigned short servidorPorta = 10110;
char IP_Servidor[15] = {"192.168.0.52"};

void monta_cliente() {
    // Construir struct sockaddr_in
    memset(&servidorAddr, 0,
           sizeof(servidorAddr));  // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);
}

void requisita_temperatura(Servidor_Struct *servStruct) {
    char buffer[30];
    unsigned int tamanhoMensagem;
    char mensagem[15];

    memset(mensagem, '\0', sizeof(mensagem));

    mensagem[0] = 'T';
    // printf("O Que eu ia enviar: %s\n", mensagem);

    tamanhoMensagem = strlen(mensagem);

    // Criar Socket
    if ((clienteTempSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()\n");

    // Connect
    int flag_connect = 1;
    while (flag_connect) {
        if(connect(clienteTempSocket, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) < 0)
            printf("Erro no connect()\n");
        else 
            flag_connect = 0;
    }

    // Enviar Mensagem
    if (send(clienteTempSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf(
            "Erro no envio: numero de bytes enviados diferente do esperado\n");

    char sinalRecebido = '0';

    // Receber Mensagem
    while (sinalRecebido != '1') {
        bzero(buffer, 30);
        recv(clienteTempSocket, buffer, 30, 0);
        if (buffer[0] == 'T') {
            float temp, hum;
            bzero(buffer, 30);
            recv(clienteTempSocket, buffer, 30, 0);
            sscanf(buffer, "%f", &temp);

            bzero(buffer, 30);
            recv(clienteTempSocket, buffer, 30, 0);
            sscanf(buffer, "%f", &hum);

            servStruct->temp = temp;
            servStruct->hum = hum;

        } else if (buffer[0] == '1') {
            sinalRecebido = buffer[0];
        } else {
            printf("Não recebeu o total de bytes enviados\n");
        }
        sleep(2);
    }

    // Fechar Conexão
    close(clienteTempSocket);
}

void envia_mensagem_distribuido(char cod_sinal, int estado_sinal, char pos) {
    char buffer[30];
    unsigned int tamanhoMensagem;
    char mensagem[15];

    memset(mensagem, '\0', sizeof(mensagem));

    mensagem[0] = cod_sinal;
    mensagem[1] = estado_sinal ? '1' : '0';
    mensagem[2] = pos;
    // printf("O Que eu ia enviar: %s\n", mensagem);

    tamanhoMensagem = strlen(mensagem);

    // Criar Socket
    if ((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()\n");

    // Connect
    if (connect(clienteSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0)
        printf("Erro no connect()\n");

    // Enviar Mensagem
    if (send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
        printf(
            "Erro no envio: numero de bytes enviados diferente do esperado\n");

    char sinalRecebido = '0';

    // Receber Mensagem
    while (sinalRecebido != '1') {
        bzero(buffer, 30);
        recv(clienteSocket, buffer, 30, 0);
        if (buffer[1] != '1') printf("Não recebeu o total de bytes enviados\n");
        sinalRecebido = buffer[0];
        // printf("[%s]\n", buffer);
        sleep(2);
    }

    // Fechar Conexão
    close(clienteSocket);
}

void fecha_cliente() {
    close(clienteSocket);
    close(clienteTempSocket);
}