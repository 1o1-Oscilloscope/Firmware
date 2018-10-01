#include <xc.h>

#ifndef PORTS_H
#define	PORTS_H

// LED ports
#define LED_1_LAT      LATGbits.LATG6
#define LED_1_PORT     PORTGbits.RG6
#define LED_1_TRIS     TRISGbits.TRISG6

#define LED_2_LAT      LATGbits.LATG7
#define LED_2_PORT     PORTGbits.RG7
#define LED_2_TRIS     TRISGbits.TRISG7

#define LED_3_LAT      LATGbits.LATG8
#define LED_3_PORT     PORTGbits.RG8
#define LED_3_TRIS     TRISGbits.TRISG8

// Gain Mux control
#define A_0_LAT      LATBbits.LATB7
#define A_0_PORT     PORTBbits.RB7
#define A_0_TRIS     TRISBbits.TRISB7

#define A_1_LAT      LATBbits.LATB8
#define A_1_PORT     PORTBbits.RB8
#define A_1_TRIS     TRISBbits.TRISB8

#define A_2_LAT      LATBbits.LATB9
#define A_2_PORT     PORTBbits.RB9
#define A_2_TRIS     TRISBbits.TRISB9

#define A_EN_LAT      LATDbits.LATD2
#define A_EN_PORT     PORTDbits.RD2
#define A_EN_TRIS     TRISDbits.TRISD2


#define PORT_INPUT  1
#define PORT_OUTPUT 0

#define PIN_DIGITAL 0
#define PIN_ANALOG  1

#define PIN_ON  1
#define PIN_OFF 0

void ports_init(void);
void pps_init(void);

#endif