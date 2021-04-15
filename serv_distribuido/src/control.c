#include "control.h"

/* Variáveis Globais do I2C */
struct identifier id_i2c;

void controle_temp(void *args) {
    /*************** Variáveis ************/

    Servidor_Struct *servStruct = (Servidor_Struct *)args;

    /* Variáveis do I2C */
    struct bme280_dev dev;

    /************ Configuração ************/
    /* Configuração do I2C */
    monta_i2c(&dev, &id_i2c);
    abre_i2c(&dev, &id_i2c);
    inicializa_bme280_i2c(&dev);
    configura_bme280_i2c(&dev);

    /* Configuração do GPIO */
    configura_GPIO();

    while (servStruct->flag_run) {
        /* I2C */
        double temp, hum;
        le_temp_bme280_i2c(&dev, &temp, &hum);
        printf("Temperatura: %lf\n", temp);
        printf("Temperatura: %lf\n", hum);

        /* GPIO */
        liga_desliga_lamp_1(servStruct->lamp1);
        sleep(1);

        liga_desliga_lamp_2(servStruct->lamp2);
        sleep(1);

        liga_desliga_lamp_3(servStruct->lamp3);
        sleep(1);

        liga_desliga_lamp_4(servStruct->lamp4);
        sleep(1);

        liga_desliga_ar_1(servStruct->ar1);
        sleep(1);

        liga_desliga_ar_2(servStruct->ar2);
        sleep(1);

        servStruct->lamp1 = servStruct->lamp1 ? 0 : 1;
        servStruct->lamp2 = servStruct->lamp2 ? 0 : 1;
        servStruct->lamp3 = servStruct->lamp3 ? 0 : 1;
        servStruct->lamp4 = servStruct->lamp4 ? 0 : 1;
        servStruct->ar1 = servStruct->ar1 ? 0 : 1;
        servStruct->ar2 = servStruct->ar2 ? 0 : 1;

    }

    /************ Finalização ************/
    fecha_conexoes();
}

void fecha_conexoes() {
    /* Finalização do I2C */
    printf("Finalizando conexão com I2C...\n");
    close(id_i2c.fd);
    printf("Finalizado!\n");

    /* Finalização do GPIO */
    printf("Finalizando conexão com GPIO...\n");
    desativa_circuito_de_potencia();
    printf("Finalizado!\n");
    printf("Tchau!\n");
    exit(0);
}
