#include <xc.h>
#include "ports.h"

void sys_init(void){
    
}

void ports_init(void){
	LED_1_LAT = 0;
	LED_1_PORT = 0;
	LED_1_TRIS = PORT_OUTPUT;
	
	LED_2_LAT = 0;
	LED_2_PORT = 0;
	LED_2_TRIS = PORT_OUTPUT;
	
	LED_3_LAT = 0;
	LED_3_PORT = 0;
	LED_3_TRIS = PORT_OUTPUT;
	
	A_0_LAT = 0;
	A_0_PORT = 0;
	A_0_TRIS = PORT_OUTPUT;

	A_1_LAT = 0;
	A_1_PORT = 0;
	A_1_TRIS = PORT_OUTPUT;

	A_2_LAT = 0;
	A_2_PORT = 0;
	A_2_TRIS = PORT_OUTPUT;

	A_EN_LAT = 0;
	A_EN_PORT = 0;
	A_EN_TRIS = PORT_OUTPUT;
}

void pps_init(void){
    // Pass
}
