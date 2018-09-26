/*
 * PMP 6800 Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   pmp_6800.c
 * 
 * @Summary
 *   Interface to operate parallel master port in 6800-series mode.
*/

#include "pmp_6800.h"

#include <xc.h>
#include <stdint.h>

#include "ports.h"

void
pmp_6800_init()
{
	PMDC_LAT = LOW;
	PMDC_PORT = 0;
	PMDC_TRIS = PORT_OUTPUT;
	
	PB2DIVbits.ON = 0;
	while (!PB2DIVbits.PBDIVRDY) {}
	PB2DIVbits.PBDIV = 13;
	PB2DIVbits.ON = 1;
	
	PMCONbits.DUALBUF = 1;
	PMCONbits.SIDL = 1;
	PMCONbits.ADRMUX = 0b00;
	PMCONbits.PMPTTL = 0;
	PMCONbits.PTWREN = 1;
	PMCONbits.PTRDEN = 1;
	PMCONbits.CSF = 0b00;
	PMCONbits.CS2P = 0;
	PMCONbits.CS1P = 0;
	PMCONbits.WRSP = 1;
	PMCONbits.RDSP = 1;
	
	PMMODEbits.IRQM = 0b00;
	PMMODEbits.INCM = 0b00;
	PMMODEbits.MODE16 = 0;
	PMMODEbits.MODE = 0b11;
	PMMODEbits.WAITB = 0b00;
	PMMODEbits.WAITM = 0b00;
	PMMODEbits.WAITE = 0b00;
	
	PMAENbits.PTEN = 0b0100000000000000;
	PMADDRbits.CS1 = 1;
	
	PMCONbits.ON = 1;
}


void
pmp_6800_write_command(uint8_t command)
{
	PMDC_LAT = LOW;
	PMDOUTbits.DATAOUT = command;
	while (PMMODEbits.BUSY) {}
}

uint8_t
pmp_6800_read_status()
{
	PMDC_LAT = LOW;
	PMCONbits.RDSTART = 1;
	while (PMCONbits.RDSTART) {}
	return (uint8_t)PMRDINbits.RDATAIN;
}

void
pmp_6800_write_data(uint8_t data)
{
	PMDC_LAT = HIGH;
	PMDOUTbits.DATAOUT = data;
	while (PMMODEbits.BUSY) {}
}

uint8_t
pmp_6800_read_data()
{
	PMDC_LAT = HIGH;
	PMCONbits.RDSTART = 1;
	while (PMCONbits.RDSTART) {}
	return (uint8_t)PMRDINbits.RDATAIN;
}
