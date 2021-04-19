#include "serverCentral.h"

int servidorSocket;
int socketCliente;

void ativaDesativaAlarme(Servidor_Struct *servStruct, char sinalSensor) {
    if (servStruct->alarme && sinalSensor == '1') {
        servStruct->sinalAlarme = 0;
    }
}

void TrataClienteTCP(int socketCliente, Servidor_Struct *servStruct) {
    char buffer[30];
    char token[5];
    int value;
    char envio[30] = {"1Menino, não é que veio?1"};
    int tamanhoRecebido;

    memset(buffer, '\0', sizeof(buffer));

    if ((tamanhoRecebido = recv(socketCliente, buffer, 30, 0)) < 0)
        printf("Erro no recv1()\n");

    switch (buffer[0]) {
        case 'P':
            switch (buffer[1]) {
                case '1':
                    servStruct->sensorPres1 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '2':
                    servStruct->sensorPres2 = (buffer[2] == '1') ? 1 : 0;
                    break;
            }
            ativaDesativaAlarme(servStruct, buffer[2]);
            break;
        case 'A':
            switch (buffer[1]) {
                case '1':
                    servStruct->sensorAbrt1 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '2':
                    servStruct->sensorAbrt2 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '3':
                    servStruct->sensorAbrt3 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '4':
                    servStruct->sensorAbrt4 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '5':
                    servStruct->sensorAbrt5 = (buffer[2] == '1') ? 1 : 0;
                    break;
                case '6':
                    servStruct->sensorAbrt6 = (buffer[2] == '1') ? 1 : 0;
                    break;
            }
            ativaDesativaAlarme(servStruct, buffer[2]);
            break;
        case 'F':
            strtok(buffer, ";");

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorPres1 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorPres2 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt1 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt2 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt3 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt4 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt5 = value;

            strcpy(token, strtok(NULL, ";"));
            sscanf(token, "%d", &value);
            servStruct->sensorAbrt6 = value;

            printf("servStruct->sensorPres1: %d\n", servStruct->sensorPres1);
            printf("servStruct->sensorPres2: %d\n", servStruct->sensorPres2);
            printf("servStruct->sensorAbrt1: %d\n", servStruct->sensorAbrt1);
            printf("servStruct->sensorAbrt2: %d\n", servStruct->sensorAbrt2);
            printf("servStruct->sensorAbrt3: %d\n", servStruct->sensorAbrt3);
            printf("servStruct->sensorAbrt4: %d\n", servStruct->sensorAbrt4);
            printf("servStruct->sensorAbrt5: %d\n", servStruct->sensorAbrt5);
            printf("servStruct->sensorAbrt6: %d\n", servStruct->sensorAbrt6);

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
            // printf("Falha no Accept\n");
            strcpy(servStruct->mensagem, "Falha no;Accept");
            servStruct->tipo_mensagem = 5;
        } else {
            // printf("Conexão do Cliente: %s\n",
            // inet_ntoa(clienteAddr.sin_addr));
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
