#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>

typedef struct arg_struct
{
    int flag_run;
    int flag_insert_temp;
    double temp_ext;
    float temp_int;
    float temp_ref_user;
    float temp_ref_pot;
    double intensity;

} Arg_Struct;

void iniciaTelas();
void atualiza_temperaturas(void *args);
void opcoes_usuario(Arg_Struct *main_struct);

#endif /* MENU_H_ */
