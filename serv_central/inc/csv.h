#ifndef CSV_H_
#define CSV_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void abre_ou_cria_csv();

void escreve_csv(int evento, char *dispositivo, char *numero);

#endif /* CSV_H_ */