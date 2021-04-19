#include "csv.h"

void abre_ou_cria_csv() {
    FILE *fpt;

    fpt = fopen("dados.csv", "w");
    fprintf(fpt, "Data, Hora, Evento, Dispositivo, Numero\n");
    fclose(fpt);
}

void escreve_csv(int evento, char *dispositivo, char *numero) {
    FILE *fpt;
    fpt = fopen("dados.csv", "a");

    time_t rawtime;
    struct tm *info;
    char dataTxt[40];
    char horaTxt[40];
    char eventoTxt[10];
    if (evento) {
        strcpy(eventoTxt, "Liga");
    } else {
        strcpy(eventoTxt, "Desliga");
    }

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(dataTxt, 40, "%d/%m/%Y", info);
    strftime(horaTxt, 40, "%H:%M:%S", info);

    fprintf(fpt, "%s, %s, %s, %s, %s\n", dataTxt, horaTxt, eventoTxt, dispositivo, numero);
    fclose(fpt);
}
