/*
 * 1o1 Port Definitions
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   ports.h
 * 
 * @Summary
 *   Defines the IO ports used by the hardware.
*/

#include <xc.h>

#ifndef PORTS_H
#define	PORTS_H

#define LED_1_LAT      LATGbits.LATG6
#define LED_1_PORT     PORTGbits.RG6
#define LED_1_TRIS     TRISGbits.TRISG6
#define LED_1_ANSEL    ANSELGbits.ANSG6

#define LED_2_LAT      LATGbits.LATG7
#define LED_2_PORT     PORTGbits.RG7
#define LED_2_TRIS     TRISGbits.TRISG7
#define LED_2_ANSEL    ANSELGbits.ANSG7

#define LED_3_LAT      LATGbits.LATG8
#define LED_3_PORT     PORTGbits.RG8
#define LED_3_TRIS     TRISGbits.TRISG8
#define LED_3_ANSEL    ANSELGbits.ANSG8

#define OLED_RES_LAT   LATDbits.LATD10
#define OLED_RES_PORT  PORTDbits.RD10
#define OLED_RES_TRIS  TRISDbits.TRISD10

#define BUT_1_LAT      LATBbits.LATB10
#define BUT_1_PORT     PORTBbits.RB10
#define BUT_1_TRIS     TRISBbits.TRISB10
#define BUT_1_CNPU     CNPUBbits.CNPUB10
#define BUT_1_ANSEL    ANSELBbits.ANSB10

#define BUT_2_LAT      LATBbits.LATB11
#define BUT_2_PORT     PORTBbits.RB11
#define BUT_2_TRIS     TRISBbits.TRISB11
#define BUT_2_CNPU     CNPUBbits.CNPUB11
#define BUT_2_ANSEL    ANSELBbits.ANSB11

#define BUT_3_LAT      LATBbits.LATB12
#define BUT_3_PORT     PORTBbits.RB12
#define BUT_3_TRIS     TRISBbits.TRISB12
#define BUT_3_CNPU     CNPUBbits.CNPUB12
#define BUT_3_ANSEL    ANSELBbits.ANSB12

#define BUT_4_LAT      LATBbits.LATB13
#define BUT_4_PORT     PORTBbits.RB13
#define BUT_4_TRIS     TRISBbits.TRISB13
#define BUT_4_CNPU     CNPUBbits.CNPUB13
#define BUT_4_ANSEL    ANSELBbits.ANSB13

#define BUT_5_LAT      LATBbits.LATB14
#define BUT_5_PORT     PORTBbits.RB14
#define BUT_5_TRIS     TRISBbits.TRISB14
#define BUT_5_CNPU     CNPUBbits.CNPUB14
#define BUT_5_ANSEL    ANSELBbits.ANSB14

#define BUT_6_LAT      LATBbits.LATB15
#define BUT_6_PORT     PORTBbits.RB15
#define BUT_6_TRIS     TRISBbits.TRISB15
#define BUT_6_CNPU     CNPUBbits.CNPUB15
#define BUT_6_ANSEL    ANSELBbits.ANSB15

#define A_0_LAT        LATBbits.LATB7
#define A_0_PORT       PORTBbits.RB7
#define A_0_TRIS       TRISBbits.TRISB7
#define A_0_ANSEL      ANSELBbits.ANSB7

#define A_1_LAT        LATBbits.LATB8
#define A_1_PORT       PORTBbits.RB8
#define A_1_TRIS       TRISBbits.TRISB8
#define A_1_ANSEL      ANSELBbits.ANSB8

#define A_2_LAT        LATBbits.LATB9
#define A_2_PORT       PORTBbits.RB9
#define A_2_TRIS       TRISBbits.TRISB9
#define A_2_ANSEL      ANSELBbits.ANSB9

#define A_EN_LAT       LATDbits.LATD2
#define A_EN_PORT      PORTDbits.RD2
#define A_EN_TRIS      TRISDbits.TRISD2


#define PORT_INPUT  1
#define PORT_OUTPUT 0

#define PIN_DIGITAL 0
#define PIN_ANALOG  1

#define PIN_ON      1
#define PIN_OFF     0


#ifdef	__cplusplus
extern "C"
{
#endif


void ports_init ();


#ifdef	__cplusplus
}
#endif

#endif /* PORTS_H */
