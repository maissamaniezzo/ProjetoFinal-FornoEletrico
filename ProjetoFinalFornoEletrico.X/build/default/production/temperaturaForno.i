# 1 "temperaturaForno.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/home/maissa/microchip/mplabx/v5.45/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "temperaturaForno.c" 2
# 1 "./temperaturaForno.h" 1
# 11 "./temperaturaForno.h"
int setTemperature();
# 2 "temperaturaForno.c" 2
# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
 void lcdData(unsigned char valor);
 void lcdInit(void);
    void lcdPosition(unsigned char linha, unsigned char coluna);
    void lcd_str(const char* str);
# 3 "temperaturaForno.c" 2
# 1 "./adc.h" 1
# 27 "./adc.h"
void adc_init(void);

unsigned int adc_amostra(unsigned char canal);
# 4 "temperaturaForno.c" 2
# 1 "./itoa.h" 1
# 26 "./itoa.h"
void itoa(unsigned int val, char* str );
# 5 "temperaturaForno.c" 2
# 1 "./atraso.h" 1



    void atraso_ms(unsigned int t);
# 6 "temperaturaForno.c" 2

int setTemperature() {
    char str[6];
    unsigned char tmp;
    int i, temperatura;

    tmp = (adc_amostra(0)*10) / 204;
    temperatura = (((int) tmp) * 4) + 50;

    itoa((char) temperatura, str);

    lcdPosition(0, 12);
    lcdData(str[2]);
    lcdData(str[3]);
    lcdData(str[4]);

    return temperatura;
}
