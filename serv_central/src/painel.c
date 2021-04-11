#include "painel.h"

#include <pthread.h>

#include "structures.h"

WINDOW *windowTempUmd, *windowEstadoAlarme;
WINDOW *windowEstadoSensores, *windowEstadoEntradas;
WINDOW *windowControleEntradas;
int pos = 0;

void iniciaTela() {
    initscr();
    start_color();
    noecho();
    clear();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
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

    // get the input
    if (ch != ERR) {
        // printf("Pegou aqui hein: %d", ch);
        // sprintf(item, "%s", listaEntradas[pos]);
        // mvwprintw(windowControleEntradas, pos + 2, 2, "%s", item);
        // use a variable to increment or decrement the value based on the
        // input.
        switch (ch) {
            case KEY_UP:
                (pos)--;
                pos = (pos < 0) ? 7 : pos;
                break;
            case KEY_DOWN:
                (pos)++;
                pos = (pos > 7) ? 0 : pos;
                break;
        }
        // // now highlight the next item in the list.
        // wattron(windowControleEntradas, A_STANDOUT);

        // sprintf(item, "%s", listaEntradas[pos]);
        // mvwprintw(windowControleEntradas, pos + 2, 2, "%s", item);
        // wattroff(windowControleEntradas, A_STANDOUT);
    }
    int i = 0;
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

void carregaMenu(void *args) {
    Servidor_Struct *servStruct = (Servidor_Struct *)args;
    windowEstadoEntradas = newwin(12, 50, 1, 1);
    windowEstadoSensores = newwin(12, 55, 1, 52);
    windowEstadoAlarme = newwin(6, 32, 13, 1);
    windowTempUmd = newwin(6, 32, 19, 1);
    windowControleEntradas = newwin(12, 73, 13, 34);

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
        sleep(1);
    }

    // pthread_join(input_tid, NULL);
}

void desliga_telas() {
    delwin(windowEstadoEntradas);
    delwin(windowEstadoSensores);
    delwin(windowEstadoAlarme);
    delwin(windowTempUmd);
    delwin(windowControleEntradas);
    echo();
    nocbreak();
    endwin();
}