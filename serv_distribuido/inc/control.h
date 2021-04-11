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

void controle_temp(void *args);

void fecha_conexoes();

#endif /* CONTROL_H_ */
