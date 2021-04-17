#ifndef PAINEL_H_
#define PAINEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include <pthread.h>

#include "server.h"
#include "structures.h"

void iniciaTela();

void carregaMenu(void *args);

void desliga_telas();

#endif /* PAINEL_H_ */
