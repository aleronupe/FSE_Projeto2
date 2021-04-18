#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "bme280.h"
#include "gpio.h"
#include "i2c.h"
#include "structures.h"

void inicia_conexoes();

void le_temp_e_umid( double *temp, double *hum);

void fecha_conexoes();

#endif /* CONTROL_H_ */
