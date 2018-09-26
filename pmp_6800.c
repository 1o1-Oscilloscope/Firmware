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

static void
set_pb2div(uint8_t setting)
{
    volatile uint32_t int_status;
    volatile uint32_t dma_suspend;

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

    /* Unlock */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    /* PBCLK2: PMP, I2C, UART, SPI */
    while (PB2DIVbits.PBDIVRDY == 0);
    PB2DIVbits.PBDIV = setting;
    PB2DIVbits.ON = 1;


    /* Lock */
    SYSKEY = 0x33333333;
    
    if (dma_suspend == 0)
    {
        DMACONCLR = _DMACON_SUSPEND_MASK;
    }

    __builtin_set_isr_state(int_status);
}

void
pmp_6800_init()
{
	PMDC_LAT = LOW;
	PMDC_PORT = 0;
	PMDC_TRIS = PORT_OUTPUT;
	
	set_pb2div(6);
	
	PMCONbits.DUALBUF = 1;
	PMCONbits.SIDL = 0;
	PMCONbits.ADRMUX = 0b00;
	PMCONbits.PMPTTL = 0;
	PMCONbits.PTWREN = 1;
	PMCONbits.PTRDEN = 1;
	PMCONbits.CSF = 0b00;
    PMCONbits.ALP = 1;
	PMCONbits.CS2P = 0;
	PMCONbits.CS1P = 0;
	PMCONbits.WRSP = 1;
	PMCONbits.RDSP = 1;
	
	PMMODEbits.IRQM = 0b00;
	PMMODEbits.INCM = 0b00;
	PMMODEbits.MODE16 = 0;
	PMMODEbits.MODE = 0b11;
	PMMODEbits.WAITB = 0b11;
	PMMODEbits.WAITM = 0b0011;
	PMMODEbits.WAITE = 0b11;
	
	PMAENbits.PTEN = 0b0100000000000000;
	PMADDRbits.CS1 = 1;
    
    //mPMPClearIntFlag();
    //mPMPSetIntPriority(0);
    //mPMPSetIntSubPriority(0);
    //mPMPIntEnable();
	
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
