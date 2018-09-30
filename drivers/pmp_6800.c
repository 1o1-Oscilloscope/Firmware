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


static void
set_pb2div (uint8_t setting)
{
	uint32_t int_status;
	uint32_t dma_suspend;
	
	// Disable global interrupt
	int_status = __builtin_get_isr_state();
	__builtin_disable_interrupts();
	
	// Suspend DMA
	dma_suspend = DMACONbits.SUSPEND;
	if (dma_suspend == 0)
	{
		DMACONSET = _DMACON_SUSPEND_MASK;
		while (DMACONbits.DMABUSY == 1);
	}
	
	// Unlock register
	SYSKEY = 0x00000000;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;
	
	// Set PB2DIV once available
	while (PB2DIVbits.PBDIVRDY == 0) {}
	PB2DIVbits.PBDIV = setting;
	PB2DIVbits.ON = 1;
	
	
	// Lock register
	SYSKEY = 0x33333333;
	
	// Restore DMA and interrupt states
	if (dma_suspend == 0)
	{
		DMACONCLR = _DMACON_SUSPEND_MASK;
	}
	__builtin_set_isr_state(int_status);
}

void
pmp_6800_init ()
{
	set_pb2div(2);

	IEC4bits.PMPEIE = 0;
	IEC4bits.PMPIE = 0;
	PMCONbits.ON = 0;

	PMCONbits.DUALBUF = 1;
	PMCONbits.SIDL = 0;
	PMCONbits.ADRMUX = 0b00;
	PMCONbits.PMPTTL = 0;
	PMCONbits.PTWREN = 1;
	PMCONbits.PTRDEN = 1;
	PMCONbits.CSF = 0b10;
	PMCONbits.ALP = 1;
	PMCONbits.CS2P = 1;
	PMCONbits.CS1P = 0;
	PMCONbits.WRSP = 1;
	PMCONbits.RDSP = 1;

	PMMODEbits.IRQM = 0b00;
	PMMODEbits.INCM = 0b00;
	PMMODEbits.MODE16 = 0;
	PMMODEbits.MODE = 0b11;
	PMMODEbits.WAITB = 0b01;
	PMMODEbits.WAITM = 0b0001;
	PMMODEbits.WAITE = 0b01;

	PMAENbits.PTEN = 0b1100000000000000;
	PMWADDRbits.WCS1 = 1;
	PMRADDRbits.RCS1 = 1;
	PMWADDRbits.WCS2 = 0;
	PMRADDRbits.RCS2 = 0;

	PMCONbits.ON = 1;
}


void
pmp_6800_write_command (uint8_t command)
{
	PMWADDRbits.WCS2 = 0;
	PMDOUT = command;
	while (PMMODEbits.BUSY) {}
}

uint8_t
pmp_6800_read_status ()
{
	PMRADDRbits.RCS2 = 0;
	while (PMMODEbits.BUSY) {}
	uint16_t inter = PMRDIN;
	while (PMMODEbits.BUSY) {}
	inter = PMRDIN;
	return (inter & 0xFF);
}

void
pmp_6800_write_data (uint8_t data)
{
	PMWADDRbits.WCS2 = 1;
	PMDOUT = data;
	while (PMMODEbits.BUSY) {}
}

uint8_t
pmp_6800_read_data ()
{
	PMRADDRbits.RCS2 = 1;
	while (PMMODEbits.BUSY) {}
	uint16_t inter = PMRDIN;
	return (inter & 0xFF);
}
