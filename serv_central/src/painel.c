#include "painel.h"

WINDOW *windowTempUmd, *windowEstadoAlarme;
WINDOW *windowEstadoSensores, *windowEstadoEntradas;
WINDOW *windowControleEntradas, *windowMensagens;
int pos = 0;
int estadoEntradas[7] = {0};

void iniciaTela() {
    initscr();
    start_color();
    noecho();
    clear();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
}

void desliga_telas() {
    delwin(windowEstadoEntradas);
    delwin(windowEstadoSensores);
    delwin(windowEstadoAlarme);
    delwin(windowTempUmd);
    delwin(windowControleEntradas);
    delwin(windowMensagens);
    echo();
    nocbreak();
    endwin();
}

char *defineLigaDesliga(int estado) {
    if (estado) {
        return "DESLIGAR";
    }
    return "---LIGAR";
}

char *defineOnOff(int estado) {
    if (estado) {
        return "-ON";
    }
    return "OFF";
}

char *defineAtivoInativo(int estado) {
    if (estado) {
        return "--ATIVO";
    }
    return "Inativo";
}

char *defineLigadoDesligado(int estado) {
    if (estado) {
        return "---Ligado";
    }
    return "Desligado";
}

void pintaWindowEstadoSensores() {
    char listaSensores[8][50] = {"Sensor de Presenca 01 (Sala):------------",
                                 "Sensor de Presenca 02 (Cozinha):---------",
                                 "Sensor Abertura 01 (Porta Cozinha):------",
                                 "Sensor Abertura 02 (Janela Cozinha):-----",
                                 "Sensor Abertura 03 (Porta Sala):---------",
                                 "Sensor Abertura 04 (Janela Sala):--------",
                                 "Sensor Abertura 05 (Janela Quarto 01):---",
                                 "Sensor Abertura 06 (Janela Quarto 02):---"};
    char item[50];
    box(windowEstadoSensores, 0, 0);
    mvwprintw(windowEstadoSensores, 0, 2, " Painel de Sensores ");

    for (int i = 0; i < 8; i++) {
        sprintf(item, "%s", listaSensores[i]);
        mvwprintw(windowEstadoSensores, i + 2, 2, "%s", item);
    }
}

void pintaWindowEstadoEntradas() {
    char listaEntradas[6][50] = {"Lampada 01 (Cozinha):-------------",
                                 "Lampada 02 (Sala):----------------",
                                 "Lampada 03 (Quarto 01):-----------",
                                 "Lampada 04 (Quarto 02):-----------",
                                 "Ar-Condicionado 01 (Quarto 01):---",
                                 "Ar-Condicionado 02 (Quarto 02):---"};
    char item[50];
    box(windowEstadoEntradas, 0, 0);
    mvwprintw(windowEstadoEntradas, 0, 2, " Painel de Luzes/Ar-Condicionado ");

    for (int i = 0; i < 6; i++) {
        sprintf(item, "%s", listaEntradas[i]);
        mvwprintw(windowEstadoEntradas, i + 3, 2, "%s", item);
    }
}

void pintaWindowEstadoAlarme() {
    char listaAlarme[2][30] = {"Alarme:------------", "Sinal do Alarme:-----"};
    char item[30];
    box(windowEstadoAlarme, 0, 0);
    mvwprintw(windowEstadoAlarme, 0, 2, " Alarme ");

    for (int i = 0; i < 2; i++) {
        sprintf(item, "%s", listaAlarme[i]);
        mvwprintw(windowEstadoAlarme, i + 2, 2, "%s", item);
    }
}

void pintaWindowTempUmidade() {
    char listaAlarme[2][30] = {"Umidade:-------", "Temperatura:---"};
    char item[30];
    box(windowTempUmd, 0, 0);
    mvwprintw(windowTempUmd, 0, 2, " Temperatura e Umidade ");

    for (int i = 0; i < 2; i++) {
        sprintf(item, "%s", listaAlarme[i]);
        mvwprintw(windowTempUmd, i + 2, 2, "%s", item);
    }
}

void pintaWindowControleEntrada() {
    char listaEntradas[8][40] = {"Lampada 01 (Cozinha):-------------",
                                 "Lampada 02 (Sala):----------------",
                                 "Lampada 03 (Quarto 01):-----------",
                                 "Lampada 04 (Quarto 02):-----------",
                                 "Ar-Condicionado 01 (Quarto 01):---",
                                 "Ar-Condicionado 02 (Quarto 02):---",
                                 "Alarme:---------------------------",
                                 "Sair"};
    int i = 0;
    char item[40];
    box(windowControleEntradas, 0, 0);
    // now print all the menu items and highlight the first one
    for (i = 0; i < 8; i++) {
        if (i == pos)
            wattron(windowControleEntradas,
                    A_STANDOUT);  // highlights the first item.
        else
            wattroff(windowControleEntradas, A_STANDOUT);
        sprintf(item, "%s", listaEntradas[i]);
        mvwprintw(windowControleEntradas, i + 2, 2, "%s", item);
    }
    wrefresh(windowControleEntradas);  // update the terminal screen
}

void atualizaWindowEstadoSensores(Servidor_Struct *servStruct) {
    mvwprintw(windowEstadoSensores, 2, 43, "%s",
              defineOnOff(servStruct->sensorPres1));
    mvwprintw(windowEstadoSensores, 3, 43, "%s",
              defineOnOff(servStruct->sensorPres2));
    mvwprintw(windowEstadoSensores, 4, 43, "%s",
              defineOnOff(servStruct->sensorAbrt1));
    mvwprintw(windowEstadoSensores, 5, 43, "%s",
              defineOnOff(servStruct->sensorAbrt2));
    mvwprintw(windowEstadoSensores, 6, 43, "%s",
              defineOnOff(servStruct->sensorAbrt3));
    mvwprintw(windowEstadoSensores, 7, 43, "%s",
              defineOnOff(servStruct->sensorAbrt4));
    mvwprintw(windowEstadoSensores, 8, 43, "%s",
              defineOnOff(servStruct->sensorAbrt5));
    mvwprintw(windowEstadoSensores, 9, 43, "%s",
              defineOnOff(servStruct->sensorAbrt6));

    wrefresh(windowEstadoSensores);  // update the terminal screen
}

void atualizaWindowEstadoEntradas(Servidor_Struct *servStruct) {
    mvwprintw(windowEstadoEntradas, 3, 36, "%s",
              defineOnOff(servStruct->lamp1));
    mvwprintw(windowEstadoEntradas, 4, 36, "%s",
              defineOnOff(servStruct->lamp2));
    mvwprintw(windowEstadoEntradas, 5, 36, "%s",
              defineOnOff(servStruct->lamp3));
    mvwprintw(windowEstadoEntradas, 6, 36, "%s",
              defineOnOff(servStruct->lamp4));
    mvwprintw(windowEstadoEntradas, 7, 36, "%s", defineOnOff(servStruct->ar1));
    mvwprintw(windowEstadoEntradas, 8, 36, "%s", defineOnOff(servStruct->ar2));

    wrefresh(windowEstadoEntradas);  // update the terminal screen
}

void atualizaWindowEstadoAlarme(Servidor_Struct *servStruct) {
    mvwprintw(windowEstadoAlarme, 2, 21, "%s",
              defineLigadoDesligado(servStruct->alarme));
    mvwprintw(windowEstadoAlarme, 3, 23, "%s",
              defineAtivoInativo(servStruct->sinalAlarme));

    wrefresh(windowEstadoAlarme);  // update the terminal screen
}

void atualizaWindowTempUmidade(Servidor_Struct *servStruct) {
    mvwprintw(windowTempUmd, 2, 16, "%.2f", servStruct->hum);
    mvwprintw(windowTempUmd, 3, 16, "%.2f", servStruct->temp);

    wrefresh(windowTempUmd);  // update the terminal screen
}

void atualizaInput(Servidor_Struct *servStruct) {
    box(windowControleEntradas, 0, 0);
    mvwprintw(windowControleEntradas, 0, 2, " Painel de Controle ");
    char listaEntradas[8][40] = {"Lampada 01 (Cozinha):-------------",
                                 "Lampada 02 (Sala):----------------",
                                 "Lampada 03 (Quarto 01):-----------",
                                 "Lampada 04 (Quarto 02):-----------",
                                 "Ar-Condicionado 01 (Quarto 01):---",
                                 "Ar-Condicionado 02 (Quarto 02):---",
                                 "Alarme:---------------------------",
                                 "Sair"};
    char item[40];
    int ch;
    ch = getch();
    if (ch != ERR) {
        switch (ch) {
            case KEY_UP:
                (pos)--;
                pos = (pos < 0) ? 7 : pos;
                break;
            case KEY_DOWN:
                (pos)++;
                pos = (pos > 7) ? 0 : pos;
                break;
            case 10:
                switch (pos) {
                    case 0:
                        servStruct->lamp1 = servStruct->lamp1 ? 0 : 1;
                        estadoEntradas[0] = estadoEntradas[0] ? 0 : 1;
                        envia_mensagem_distribuido('L', servStruct->lamp1, '1');
                        escreve_csv(servStruct->lamp1, "Lampada", "1");
                        break;
                    case 1:
                        servStruct->lamp2 = servStruct->lamp2 ? 0 : 1;
                        estadoEntradas[1] = estadoEntradas[1] ? 0 : 1;
                        envia_mensagem_distribuido('L', servStruct->lamp2, '2');
                        escreve_csv(servStruct->lamp2, "Lampada", "2");
                        break;
                    case 2:
                        servStruct->lamp3 = servStruct->lamp3 ? 0 : 1;
                        estadoEntradas[2] = estadoEntradas[2] ? 0 : 1;
                        envia_mensagem_distribuido('L', servStruct->lamp3, '3');
                        escreve_csv(servStruct->lamp3, "Lampada", "3");
                        break;
                    case 3:
                        servStruct->lamp4 = servStruct->lamp4 ? 0 : 1;
                        estadoEntradas[3] = estadoEntradas[3] ? 0 : 1;
                        envia_mensagem_distribuido('L', servStruct->lamp4, '4');
                        escreve_csv(servStruct->lamp4, "Lampada", "4");
                        break;
                    case 4:
                        servStruct->ar1 = servStruct->ar1 ? 0 : 1;
                        estadoEntradas[4] = estadoEntradas[4] ? 0 : 1;
                        envia_mensagem_distribuido('A', servStruct->ar1, '1');
                        escreve_csv(servStruct->ar1, "Ar Condicionado", "1");
                        break;
                    case 5:
                        servStruct->ar2 = servStruct->ar2 ? 0 : 1;
                        estadoEntradas[5] = estadoEntradas[5] ? 0 : 1;
                        envia_mensagem_distribuido('A', servStruct->ar2, '2');
                        escreve_csv(servStruct->ar2, "Ar Condicionado", "2");
                        break;
                    case 6:
                        servStruct->alarme = servStruct->alarme ? 0 : 1;
                        servStruct->sinalAlarme =
                            servStruct->alarme ? servStruct->sinalAlarme : 0;
                        estadoEntradas[6] = estadoEntradas[6] ? 0 : 1;
                        escreve_csv(servStruct->alarme, "Alarme", "-");
                        break;
                    case 7:
                        servStruct->flag_run = 0;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    int i = 0;
    for (i = 0; i < 8; i++) {
        if (i == pos)
            wattron(windowControleEntradas, A_STANDOUT);
        else
            wattroff(windowControleEntradas, A_STANDOUT);

        sprintf(item, "%s", listaEntradas[i]);
        if (i < 7)
            mvwprintw(windowControleEntradas, i + 2, 2, "%s%s", item,
                      defineLigaDesliga(estadoEntradas[i]));
        else
            mvwprintw(windowControleEntradas, i + 2, 2, "%s", item);
    }
    wrefresh(windowControleEntradas);  // update the terminal screen
}

void atualizaMensagem(Servidor_Struct *servStruct) {
    box(windowMensagens, 0, 0);
    mvwprintw(windowMensagens, 0, 6, " Mensagens ");

    switch (servStruct->tipo_mensagem) {
        case 1:
            wattron(windowMensagens, COLOR_PAIR(1));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Estado");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Inicial");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(1));
            break;
        case 2:
            wattron(windowMensagens, COLOR_PAIR(2));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Aguardando");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Servidor");
            mvwprintw(windowMensagens, 5, 2, "%-22s", "Distribuido");
            wattroff(windowMensagens, COLOR_PAIR(2));
            break;
        case 3:
            wattron(windowMensagens, COLOR_PAIR(1));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Conexão");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Estabelecida");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(1));
            break;
        case 4:
            wattron(windowMensagens, COLOR_PAIR(2));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Pronto para");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Aceitar cliente");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(2));
            break;
        case 5:
            wattron(windowMensagens, COLOR_PAIR(5));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Falha no");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Accept");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(5));
            break;
        case 6:
            wattron(windowMensagens, COLOR_PAIR(1));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Conexão");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Estabelecida");
            mvwprintw(windowMensagens, 5, 2, "%-22s", "Com Cliente ");
            wattroff(windowMensagens, COLOR_PAIR(1));
            break;
        case 7:
            wattron(windowMensagens, COLOR_PAIR(3));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Aguarde...");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Conectando");
            mvwprintw(windowMensagens, 5, 2, "%-22s", "ao Servidor ");
            wattroff(windowMensagens, COLOR_PAIR(3));
            break;
        case 8:
            wattron(windowMensagens, COLOR_PAIR(4));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Requisição");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Realizada");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(4));
            break;
        case 9:
            wattron(windowMensagens, COLOR_PAIR(5));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "Matou o");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "Processo");
            mvwprintw(windowMensagens, 5, 2, "%-22s", " ");
            wattroff(windowMensagens, COLOR_PAIR(5));
            break;
        case 10:
            wattron(windowMensagens, COLOR_PAIR(5));
            mvwprintw(windowMensagens, 3, 2, "%-22s", "ALERTA:");
            mvwprintw(windowMensagens, 4, 2, "%-22s", "ALARME");
            mvwprintw(windowMensagens, 5, 2, "%-22s", "ATIVADOA ");
            wattroff(windowMensagens, COLOR_PAIR(5));
            break;
    }

    wrefresh(windowMensagens);
}

void carregaMenu(void *args) {
    Servidor_Struct *servStruct = (Servidor_Struct *)args;
    windowEstadoEntradas = newwin(12, 50, 1, 1);
    windowEstadoSensores = newwin(12, 55, 1, 52);
    windowEstadoAlarme = newwin(6, 32, 13, 1);
    windowTempUmd = newwin(6, 32, 19, 1);
    windowControleEntradas = newwin(12, 47, 13, 60);
    windowMensagens = newwin(12, 25, 13, 34);

    while (servStruct->flag_run) {
        pintaWindowEstadoEntradas();
        pintaWindowEstadoSensores();
        pintaWindowEstadoAlarme();
        pintaWindowTempUmidade();
        // pintaWindowControleEntrada();

        atualizaWindowEstadoEntradas(servStruct);
        atualizaWindowEstadoSensores(servStruct);
        atualizaWindowEstadoAlarme(servStruct);
        atualizaWindowTempUmidade(servStruct);
        atualizaInput(servStruct);
        atualizaMensagem(servStruct);
    }

    // pthread_join(input_tid, NULL);
}
