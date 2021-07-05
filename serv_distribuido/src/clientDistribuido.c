#include "clientDistribuido.h"

int clienteSocket;
int clienteInitialSocket;
struct sockaddr_in servidorAddr;
unsigned short servidorPorta = 10010;
char IP_Servidor[15] = {"192.168.0.53"};

void monta_cliente() {
    // Construir struct sockaddr_in
    memset(&servidorAddr, 0,
           sizeof(servidorAddr));  // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
    servidorAddr.sin_port = htons(servidorPorta);
}

void envia_mensagem_central(char cod_sinal, char pos, int estado_sinal) {
    char buffer[30];
    unsigned int tamanhoMensagem;
    char mensagem[15];

    memset(mensagem, '\0', sizeof(mensagem));

    mensagem[0] = cod_sinal;
    mensagem[1] = pos;
    mensagem[2] = estado_sinal ? '1' : '0';
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
        if (buffer[0] != '1') printf("Não recebeu o total de bytes enviados\n");
        sinalRecebido = buffer[0];
        sleep(2);
    }

    // Fechar Conexão
    close(clienteSocket);
}

void *envia_mensagem_inicial(char *initial_message, Servidor_Struct *servStruct,
                            int *flag_done) {
    char buffer[30];
    unsigned int tamanhoMensagem;
    char mensagem[30];

    memset(mensagem, '\0', sizeof(mensagem));
    strcpy(mensagem, initial_message);
    tamanhoMensagem = strlen(mensagem);

    // Criar Socket
    if ((clienteInitialSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("Erro no socket()\n");

    // Connect
    if (connect(clienteInitialSocket, (struct sockaddr *)&servidorAddr,
                sizeof(servidorAddr)) < 0) {
        printf("Não conectou ao servidor inicial\n");
        sleep(1);
        return NULL;
    } else {
        printf("Conexão Estabelecida\n");
        *flag_done = 0;
    }

    // Enviar Mensagem
    if (send(clienteInitialSocket, mensagem, tamanhoMensagem, 0) !=
        tamanhoMensagem)
        printf(
            "Erro no envio: numero de bytes enviados diferente do esperado\n");

    char sinalRecebido = '0';

    // Receber Mensagem
    while (sinalRecebido != '1') {
        bzero(buffer, 30);
        recv(clienteInitialSocket, buffer, 30, 0);
        if (buffer[0] != '1') printf("Não recebeu o total de bytes enviados\n");
        sinalRecebido = buffer[0];
        sleep(2);
    }
    // Fechar Conexão
    close(clienteInitialSocket);
    return NULL;
}

void fecha_cliente() {
    close(clienteSocket);
    close(clienteInitialSocket);
}