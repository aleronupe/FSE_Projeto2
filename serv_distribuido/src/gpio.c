#include <softPwm.h>  //Used for GPIO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>  //Used for GPIO

/* Variáveis Globais do GPIO */
#define PWM_PIN_LAMP_01 0
#define PWM_PIN_LAMP_02 1
#define PWM_PIN_LAMP_03 2
#define PWM_PIN_LAMP_04 3
#define PWM_PIN_AR_01 23
#define PWM_PIN_AR_02 24

void configura_GPIO() {
    wiringPiSetup();

    // Configura Lâmpadas
    pinMode(PWM_PIN_LAMP_01, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_01, 1, 100);

    pinMode(PWM_PIN_LAMP_02, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_02, 1, 100);

    pinMode(PWM_PIN_LAMP_03, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_03, 1, 100);

    pinMode(PWM_PIN_LAMP_04, OUTPUT);
    softPwmCreate(PWM_PIN_LAMP_04, 1, 100);

    // Configura Ar-Condicionado
    pinMode(PWM_PIN_AR_01, OUTPUT);
    softPwmCreate(PWM_PIN_AR_01, 1, 100);

    pinMode(PWM_PIN_AR_02, OUTPUT);
    softPwmCreate(PWM_PIN_AR_02, 1, 100);
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
