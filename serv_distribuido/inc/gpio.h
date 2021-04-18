#ifndef GPIO_H_
#define GPIO_H_

#include <softPwm.h>  //Used for GPIO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>  //Used for GPIO

#include "client.h"

void configura_GPIO();

void liga_desliga_lamp_1(int estado);

void liga_desliga_lamp_2(int estado);

void liga_desliga_lamp_3(int estado);

void liga_desliga_lamp_4(int estado);

void liga_desliga_ar_1(int estado);

void liga_desliga_ar_2(int estado);

void desativa_circuito_de_potencia();

#endif /* GPIO_H_ */