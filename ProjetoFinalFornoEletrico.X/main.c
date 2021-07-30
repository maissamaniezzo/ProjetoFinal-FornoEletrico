// Nome: Maíssa Maniezzo de Oliveira
// Matrícula: 2020004486  Turma: T02
// Data: 15/07/2021  Matéria: ECOP14

#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include "temperaturaForno.h"
#include "adc.h"
#include "pwm.h"
#include "itoa.h"
#include "atraso.h"


void main(void) {
    unsigned int tecla = 16;
    unsigned int temperatura = 180, temperaturaMaxima, temperaturaMinima;
    char minutosCentena = 48, minutosDezena = 48, minutosUnidade = 48;
    
    char str[6];
    char tempoRelogio[6];
    unsigned int tmpi, temperaturaLcd, tempoTotal = 0;
    
    TRISA = 0x07;
    TRISB = 0x00;
    TRISC = 0x00;
    
    lcdInit();
    kpInit();
    
    for (;;) {
        lcdPosition(0, 1);
        
        lcd_str("Vamos iniciar!");
        lcdPosition(1, 1);
        lcd_str("Clique em (1)");
        
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (bitTst(tecla, 3)) {  // Referente a tecla de número 1 -> aumenta horas 
                lcdCommand(0x01);
                while (!bitTst(tecla, 0)) {
                    // Impressão e coleta de temperatura
                    lcdPosition(0, 0);
                    lcd_str("Temperatura:");
                    temperatura = setTemperature();
                    
                    // Impressão e coleta de tempo
                    lcdPosition(1, 0);
                    lcd_str("Tempo:");
                    lcdPosition(1, 6);
                    lcdData((char)minutosCentena);
                    lcdData((char)minutosDezena);
                    lcdData((char)minutosUnidade);
                    lcd_str("min");
                    
                    // Muda valor do tempo pelos botões 7, 8, 9 e reconhece que * foi apertado
                    kpDebounce();
                    if (kpRead() != tecla) {
                        tecla = kpRead();
                        if (bitTst(tecla, 1)) {
                            if (minutosCentena == 57) {
                                minutosCentena = 48;
                            } else { 
                                minutosCentena += 1; 
                                tempoTotal += 100;
                            }
                        } else if (bitTst(tecla, 5)) {
                            if (minutosDezena == 57) {
                                minutosDezena = 48;
                            } else { 
                                minutosDezena += 1; 
                                tempoTotal += 10;
                            }
                        } else if (bitTst(tecla, 9)) {
                            if (minutosUnidade == 57) {
                                minutosUnidade = 48;
                            } else { 
                                minutosUnidade += 1; 
                                tempoTotal += 1;
                            }
                        }
                    }
                }
                
                if (bitTst(tecla, 0)) {
                    lcdCommand(0x01);
                    
                    temperaturaMaxima = temperatura + 10;
                    temperaturaMinima = temperatura - 10;
                    
                    // Configura potência do cooler (simular vida real)
                    pwmInit();
                    pwmSet1(30);
                    
                    PORTB = 0xFF;
                    
                    while ((!bitTst(tecla, 4) && (tempoTotal > 0))) { // Referente a tecla *
                        lcdCommand(0x01);
                        
                        lcdPosition(0, 2);
                        lcd_str("Funcionando!");

                        lcdPosition(1, 9);
                        itoa(tempoTotal, tempoRelogio);
                        lcdData(tempoRelogio[2]);
                        lcdData(tempoRelogio[3]);
                        lcdData(tempoRelogio[4]);
                        lcd_str("min");
                        tempoTotal--;
                        
                        // Lê temperatura
                        tmpi = (adc_amostra(1)*10) / 2;
                        temperaturaLcd = ((tmpi - 280) * 222 / 46) + 280;
                        
                        // Impressão da temperatura na tela
                        lcdPosition(1, 1);
                        itoa(temperaturaLcd, str);
                        lcdData(str[1]);
                        lcdData(str[2]);
                        lcdData(str[3]);
                        lcdData(',');
                        lcdData(str[4]);
                        lcd_str("C");
                        
                        atraso_ms(1000);
                        

                        if (temperaturaLcd > temperaturaMaxima * 10) {
                            atraso_ms(100);
                            PORTCbits.RC5 = 0; // Desliga heater
                        }

                        if (temperaturaLcd < temperaturaMinima * 10) {
                            PORTCbits.RC5 = 1; // Liga o heater
                        }
                        
                        kpDebounce();
                        if (kpRead() != tecla) {
                            tecla = kpRead();
                        } 
                    }
                }
                PORTB = 0x00;
                lcdCommand(0x01);
                PORTCbits.RC5 = 0;
                TRISCbits.TRISC0 = 0;
                pwmSet1(0);
            }
        }
    }
}