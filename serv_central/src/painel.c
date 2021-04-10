#include "painel.h"

#include "structures.h"

WINDOW *windowTempUmd, *windowEstadoAlarme;
WINDOW *windowEstadoSensores, *windowEstadoEntradas;
WINDOW *windowControleEntradas, *windowControleAlarme;

void iniciaTela() {
    initscr();
    start_color();
    noecho();
    clear();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
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

void criaWindowEstadoSensores() {
    char listaSensores[8][50] = {
        "Sensor de Presenca 01 (Sala):------------OFF",
        "Sensor de Presenca 02 (Cozinha):---------OFF",
        "Sensor Abertura 01 (Porta Cozinha):------OFF",
        "Sensor Abertura 02 (Janela Cozinha):-----OFF",
        "Sensor Abertura 03 (Porta Sala):---------OFF",
        "Sensor Abertura 04 (Janela Sala):--------OFF",
        "Sensor Abertura 05 (Janela Quarto 01):---OFF",
        "Sensor Abertura 06 (Janela Quarto 02):---OFF"};
    char item[50];
    windowEstadoSensores = newwin(12, 55, 1, 52);
    box(windowEstadoSensores, 0, 0);
    mvwprintw(windowEstadoSensores, 0, 2, " Painel de Sensores ");

    for (int i = 0; i < 8; i++) {
        sprintf(item, "%s", listaSensores[i]);
        mvwprintw(windowEstadoSensores, i + 2, 2, "%s", item);
    }
}

void criaWindowEstadoEntradas() {
    char listaEntradas[6][50] = {"Lampada 01 (Cozinha):-------------OFF",
                                 "Lampada 02 (Sala):----------------OFF",
                                 "Lampada 03 (Quarto 01):-----------OFF",
                                 "Lampada 04 (Quarto 02):-----------OFF",
                                 "Ar-Condicionado 01 (Quarto 01):---OFF",
                                 "Ar-Condicionado 02 (Quarto 02):---OFF"};
    char item[50];
    windowEstadoEntradas = newwin(12, 50, 1, 1);
    box(windowEstadoEntradas, 0, 0);
    mvwprintw(windowEstadoEntradas, 0, 2, " Painel de Controle ");

    for (int i = 0; i < 6; i++) {
        sprintf(item, "%s", listaEntradas[i]);
        mvwprintw(windowEstadoEntradas, i + 3, 2, "%s", item);
    }
}

void criaWindowEstadoAlarme() {
    char listaAlarme[2][30] = {"Alarme:------------Desligado",
                               "Sinal do Alarme:-----Inativo"};
    char item[30];
    windowEstadoAlarme = newwin(6, 32, 13, 1);
    box(windowEstadoAlarme, 0, 0);
    mvwprintw(windowEstadoAlarme, 0, 2, " Alarme ");

    for (int i = 0; i < 2; i++) {
        sprintf(item, "%s", listaAlarme[i]);
        mvwprintw(windowEstadoAlarme, i + 2, 2, "%s", item);
    }
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
    sleep(1);
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
    sleep(1);
}

void atualizaWindowEstadoAlarme(Servidor_Struct *servStruct) {
    mvwprintw(windowEstadoAlarme, 2, 21, "%s",
              defineLigadoDesligado(servStruct->alarme));
    mvwprintw(windowEstadoAlarme, 3, 23, "%s",
              defineAtivoInativo(servStruct->sinalAlarme));

    wrefresh(windowEstadoAlarme);  // update the terminal screen
    sleep(1);
}

void carregaMenu(void *args) {
    Servidor_Struct *servStruct = (Servidor_Struct *)args;
    iniciaTela();
    criaWindowEstadoEntradas();
    criaWindowEstadoSensores();
    criaWindowEstadoAlarme();
    while (servStruct->flag_run) {
        atualizaWindowEstadoEntradas(servStruct);
        atualizaWindowEstadoSensores(servStruct);
        atualizaWindowEstadoAlarme(servStruct);
    }
    wclear(windowEstadoEntradas);
    wclear(windowEstadoSensores);
    wclear(windowEstadoAlarme);
    echo();
    nocbreak();
    endwin();
}

void carrega_outro_menu() {
    // WINDOW *w;
    // char list[5][7] = {"One", "Two", "Three", "Four", "Five"};
    // char item[7];
    // int ch, i = 0, width = 7;

    // initscr();                 // initialize Ncurses
    // w = newwin(10, 12, 1, 1);  // create a new window
    // box(w, 0, 0);              // sets default borders for the window

    // // now print all the menu items and highlight the first one
    // for (i = 0; i < 5; i++) {
    //     if (i == 0)
    //         wattron(w, A_STANDOUT);  // highlights the first item.
    //     else
    //         wattroff(w, A_STANDOUT);
    //     sprintf(item, "%-7s", list[i]);
    //     mvwprintw(w, i + 1, 2, "%s", item);
    // }

    // wrefresh(w);  // update the terminal screen

    // i = 0;
    // noecho();         // disable echoing of characters on the screen
    // keypad(w, TRUE);  // enable keyboard input for the window.
    // curs_set(0);      // hide the default screen cursor.

    // // get the input
    // while ((ch = wgetch(w)) != 'q') {
    //     // right pad with spaces to make the items appear with even width.
    //     sprintf(item, "%-7s", list[i]);
    //     mvwprintw(w, i + 1, 2, "%s", item);
    //     // use a variable to increment or decrement the value based on the
    //     // input.
    //     switch (ch) {
    //         case KEY_UP:
    //             i--;
    //             i = (i < 0) ? 4 : i;
    //             break;
    //         case KEY_DOWN:
    //             i++;
    //             i = (i > 4) ? 0 : i;
    //             break;
    //     }
    //     // now highlight the next item in the list.
    //     wattron(w, A_STANDOUT);

    //     sprintf(item, "%-7s", list[i]);
    //     mvwprintw(w, i + 1, 2, "%s", item);
    //     wattroff(w, A_STANDOUT);
    // }

    // delwin(w);
    // endwin();
}