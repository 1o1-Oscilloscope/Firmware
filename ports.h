#include <xc.h>

#ifndef PORTS_H
#define	PORTS_H

#define LED_1_LAT      LATGbits.LATG6
#define LED_1_PORT     PORTGbits.RG6
#define LED_1_TRIS     TRISGbits.TRISG6

#define LED_2_LAT      LATGbits.LATG7
#define LED_2_PORT     PORTGbits.RG7
#define LED_2_TRIS     TRISGbits.TRISG7

#define LED_3_LAT      LATGbits.LATG8
#define LED_3_PORT     PORTGbits.RG8
#define LED_3_TRIS     TRISGbits.TRISG8

#define OLED_RES_LAT  LATDbits.LATD10
#define OLED_RES_PORT PORTDbits.RD10
#define OLED_RES_TRIS TRISDbits.TRISD10


#define PORT_INPUT  1
#define PORT_OUTPUT 0

#define PIN_DIGITAL 0
#define PIN_ANALOG  1

#define HIGH 1
#define LOW 0


void ports_init(void);
void pps_init(void);

#endif