#include <softPwm.h>  //Used for GPIO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>  //Used for GPIO

/* Variáveis Globais do GPIO */
// Define Pinos de Entrada de dados
#define PWM_PIN_LAMP_01 0
#define PWM_PIN_LAMP_02 1
#define PWM_PIN_LAMP_03 2
#define PWM_PIN_LAMP_04 3
#define PWM_PIN_AR_01 23
#define PWM_PIN_AR_02 24

// Define Pinos de Saída de dados
#define PIN_PRES_01 6
#define PIN_PRES_02 25
#define PIN_ABER_01 21
#define PIN_ABER_02 22
#define PIN_ABER_03 26
#define PIN_ABER_04 27
#define PIN_ABER_05 28
#define PIN_ABER_06 29

void handle_pres_1(void) {
    printf("Ativou o Sensor Presença 1\n");
}

void handle_pres_2(void) {
    printf("Ativou o Sensor Presença 2\n");
}

void handle_aber_1(void) {
    printf("Ativou o Sensor Abertura 1\n");
}

void handle_aber_2(void) {
    printf("Ativou o Sensor Abertura 2\n");
}

void handle_aber_3(void) {
    printf("Ativou o Sensor Abertura 3\n");
}

void handle_aber_4(void) {
    printf("Ativou o Sensor Abertura 4\n");
}

void handle_aber_5(void) {
    printf("Ativou o Sensor Abertura 5\n");
}

void handle_aber_6(void) {
    printf("Ativou o Sensor Abertura 6\n");
}

void configura_GPIO() {
    wiringPiSetup();

    /* Configura Lâmpadas */
    pinMode(PWM_PIN_LAMP_01, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_01, 1, 100);

    pinMode(PWM_PIN_LAMP_02, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_02, 1, 100);

    pinMode(PWM_PIN_LAMP_03, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_03, 1, 100);

    pinMode(PWM_PIN_LAMP_04, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_04, 1, 100);

    /* Configura Ar-Condicionado*/
    pinMode(PWM_PIN_AR_01, OUTPUT);
    softPwmCreate(PWM_PIN_AR_01, 1, 100);

    pinMode(PWM_PIN_AR_02, OUTPUT);
    softPwmCreate(PWM_PIN_AR_02, 1, 100);

    /* Configura Sensores */
    wiringPiISR(PIN_PRES_01, INT_EDGE_RISING, &handle_pres_1);

    wiringPiISR(PIN_PRES_02, INT_EDGE_RISING, &handle_pres_2);

    wiringPiISR(PIN_ABER_01, INT_EDGE_RISING, &handle_aber_1);

    wiringPiISR(PIN_ABER_02, INT_EDGE_RISING, &handle_aber_2);

    wiringPiISR(PIN_ABER_03, INT_EDGE_RISING, &handle_aber_3);

    wiringPiISR(PIN_ABER_04, INT_EDGE_RISING, &handle_aber_4);

    wiringPiISR(PIN_ABER_05, INT_EDGE_RISING, &handle_aber_5);

    wiringPiISR(PIN_ABER_06, INT_EDGE_RISING, &handle_aber_6);

}

void liga_desliga_lamp_1(int estado) {
    softPwmWrite(PWM_PIN_LAMP_01, 100 * estado);
    if (estado) {
        printf("Ligou a Lâmpada 1\n");
    } else {
        printf("Desligou a Lâmpada 1\n");
    }
}

void liga_desliga_lamp_2(int estado) {
    softPwmWrite(PWM_PIN_LAMP_02, 100 * estado);
    if (estado) {
        printf("Ligou a Lâmpada 2\n");
    } else {
        printf("Desligou a Lâmpada 2\n");
    }
}

void liga_desliga_lamp_3(int estado) {
    softPwmWrite(PWM_PIN_LAMP_03, 100 * estado);
    if (estado) {
        printf("Ligou a Lâmpada 3\n");
    } else {
        printf("Desligou a Lâmpada 3\n");
    }
}

void liga_desliga_lamp_4(int estado) {
    softPwmWrite(PWM_PIN_LAMP_04, 100 * estado);
    if (estado) {
        printf("Ligou a Lâmpada 4\n");
    } else {
        printf("Desligou a Lâmpada 4\n");
    }
}

void liga_desliga_ar_1(int estado) {
    softPwmWrite(PWM_PIN_AR_01, 100 * estado);
    if (estado) {
        printf("Ligou o Ar 1\n");
    } else {
        printf("Desligou o Ar 1\n");
    }
}

void liga_desliga_ar_2(int estado) {
    softPwmWrite(PWM_PIN_AR_02, 100 * estado);
    if (estado) {
        printf("Ligou o Ar 2\n");
    } else {
        printf("Desligou o Ar 2\n");
    }
}

void desativa_circuito_de_potencia() {
    // Desativa Lâmpadas
    softPwmWrite(PWM_PIN_LAMP_01, 0);
    usleep(100000);

    softPwmWrite(PWM_PIN_LAMP_02, 0);
    usleep(100000);

    softPwmWrite(PWM_PIN_LAMP_03, 0);
    usleep(100000);

    softPwmWrite(PWM_PIN_LAMP_04, 0);
    usleep(100000);

    // Desativa Ar-Condicionado
    softPwmWrite(PWM_PIN_AR_01, 0);
    usleep(100000);

    softPwmWrite(PWM_PIN_AR_02, 0);
    usleep(100000);
}
