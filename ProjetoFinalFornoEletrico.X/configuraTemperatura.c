// ECOP14 - Lab 12
// Nome: Maíssa maniezzo de Oliveira
// Matrícula: 2020004486

#include <pic18f4520.h>
#include "config.h"
#include "atraso.h"
#include "lcd.h"
#include "adc.h"
#include "pwm.h"
#include "itoa.h"
#include "configuraTemperatura.h"

unsigned char i,cnt, perc;


char tmax;
char tmin;

void ConfiguraLimiteSuperior(char temp) {
    tmax = temp;
}


void ConfiguraLimiteInferior(char temp) {
    tmin = temp;
}


void AtualizarSistema(void) { 
    
}