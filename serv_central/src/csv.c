#include "csv.h"

void abre_ou_cria_csv() {
    FILE *fpt;

    fpt = fopen("dados.csv", "w");
    fprintf(fpt, "Data/Hora, Evento, Dispositivo, Numero\n");
    fclose(fpt);
}

void escreve_csv(int evento, char *dispositivo, char *numero) {
    FILE *fpt;
    fpt = fopen("dados.csv", "a");

    time_t rawtime;
    struct tm *info;
    char dataHora[80];
    char evento_txt[10];
    if (evento) {
        strcpy(evento_txt, "Liga");
    } else {
        strcpy(evento_txt, "Desliga");
    }

    time(&rawtime);

    info = localtime(&rawtime);

    strftime(dataHora, 80, "%d/%m/%Y %H:%M:%S", info);

    fprintf(fpt, "%s, %s, %s, %s\n", dataHora, evento_txt, dispositivo, numero);
    fclose(fpt);
}
