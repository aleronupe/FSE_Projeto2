#include "control.h"

/* Variáveis Globais do I2C */
struct identifier id_i2c;

/* Variáveis do I2C */
struct bme280_dev dev;

int alt = 0;

void inicia_conexoes() {
    /************ Configuração ************/
    /* Configuração do I2C */
    // monta_i2c(&dev, &id_i2c);
    // abre_i2c(&dev, &id_i2c);
    // inicializa_bme280_i2c(&dev);
    // configura_bme280_i2c(&dev);

    /* Configuração do GPIO */
    configura_GPIO();
}

void le_temp_e_umid(double *temp, double *hum) {
    // le_temp_bme280_i2c(&dev, temp, hum);
    if (alt) {
        *temp = 25.6756;
        *hum = 56.7654;
        alt = 0;
    } else {
        *temp = 38.0101;
        *hum = 72.6924;
        alt = 1;
    }

    printf("Temperatura: %.4lf\n", *temp);
    printf("Umidade: %.4lf\n", *hum);
}

void fecha_conexoes() {
    /* Finalização do I2C */
    printf("Finalizando conexão com I2C...\n");
    // close(id_i2c.fd);
    printf("Finalizado!\n");

    /* Finalização do GPIO */
    printf("Finalizando conexão com GPIO...\n");
    desativa_circuito_de_potencia();
    printf("Finalizado!\n");
    printf("Tchau!\n");
    exit(0);
}
