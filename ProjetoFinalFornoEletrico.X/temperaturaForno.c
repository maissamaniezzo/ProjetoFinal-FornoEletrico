#include "temperaturaForno.h"
#include "lcd.h"
#include "adc.h"
#include "itoa.h"
#include "atraso.h"

int setTemperature() {
    char str[6];
    unsigned char tmp;
    int i, temperatura;

    tmp = (adc_amostra(0)*10) / 204;
    temperatura = (((int) tmp) * 4) + 50; // passa voltagem para °C

    itoa((char) temperatura, str);

    lcdPosition(0, 12);
    lcdData(str[2]);
    lcdData(str[3]);
    lcdData(str[4]);
    
    return temperatura;
}