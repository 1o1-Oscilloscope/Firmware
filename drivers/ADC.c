// Code from Microchip AN2785: http://www.microchip.com//wwwAppNotes/AppNotes.aspx?appnote=en607308

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "ADC.h"

void init_ADC(void)
{
    ADC0CFG = DEVADC0;        //Load ADC0 Calibration values
    ADC1CFG = DEVADC1;        //Load ADC1 Calibration values
    ADC2CFG = DEVADC2;        //Load ADC2 Calibration values
    ADC3CFG = DEVADC3;        //Load ADC3 Calibration values
    ADC4CFG = DEVADC4;        //Load ADC4 Calibration values
    ADC7CFG = DEVADC7;        //Load ADC7 Calibration values

    ADCANCONbits.WKUPCLKCNT = 0x9; // ADC Warm up delay = (512 * TADx)
    ADCCON1bits.AICPMPEN = 0;	   //Disable ADC charge pump
    CFGCONbits.IOANCPEN = 0;	   //Disable ADC I/O charge pump

    ADCCON1bits.FSSCLKEN = 1;	//Fast synchronous SYSCLK to ADC control clock is enabled
    ADCCON3bits.ADCSEL = 1;        	// Select ADC input clock source = SYSCLK 200Mhz
    ADCCON3bits.CONCLKDIV = 1;     	// Analog-to-Digital Control Clock (TQ) Divider = SYSCLK/2

    // ADC0 Module setup: TAD = SYSCLK/4, 6bit, SAMC=3TAD, OC1 Trigger
    ANSELBSET = 0x1;		//Enable analog AN0 input
    ADC0TIMEbits.ADCDIV = 1;		// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC0TIMEbits.SAMC = 1;		// 3 TAD (Hardware enforced sample time)
    ADC0TIMEbits.SELRES = 0;	// ADC0 6bit resolution mode
    ADCTRG1bits.TRGSRC0 = 8;	// Set AN0 to trigger from OC1
    ADCANCONbits.ANEN0 = 1;		// Enable ADC0 analog bias/logic
    ADCCON3bits.DIGEN0 = 1;		// Enable ADC0 digital logic
    ADCGIRQEN1bits.AGIEN0 = 1;	//Enb ADC0 AN0 interrupts for DMA

    // ADC1 Module setup: TAD = SYSCLK/4, 6bit, SAMC=3TAD
    ANSELBSET = 0x2;		//Enable analog AN1 input
    ADC1TIMEbits.ADCDIV = 1;		// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC1TIMEbits.SAMC = 1;		// 3 TAD
    ADC1TIMEbits.SELRES = 0;	// ADC1 6bit resolution mode

    ADCTRG1bits.TRGSRC1 = 9;	// Set ADC1 to trigger from OC3

    ADCANCONbits.ANEN1 = 1;		// Enable ADC1 analog bias/logic
    ADCCON3bits.DIGEN1 = 1;		// Enable ADC1 digital logic
    ADCGIRQEN1bits.AGIEN1 = 1;	//Enb ADC1 AN1 interrupts for DMA

    // ADC2 Module setup: TAD = SYSCLK/4, 6bit, SAMC=3TAD, OC5 Trigger
    ANSELBSET = 0x4;		//Enable analog AN2 input
    ADC2TIMEbits.ADCDIV = 1;	// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC2TIMEbits.SAMC = 1;	// 3 TAD
    ADC2TIMEbits.SELRES = 0;	// ADC2 6bit resolution mode

    ADCTRG1bits.TRGSRC2 = 10; // Set ADC2 to trigger from OC5

    ADCANCONbits.ANEN2 = 1;	// Enable ADC2 analog bias/logic
    ADCCON3bits.DIGEN2 = 1;	// Enable ADC2 digital logic      
    ADCGIRQEN1bits.AGIEN2 = 1;	//Enb ADC2 AN2 interrupts for DMA

    // ADC3 Module setup: TAD = SYSCLK/4, 6bit, SAMC=3TAD, TMR3 Trigger
    ANSELBSET = 0x8;		//Enable analog AN3 input
    ADC3TIMEbits.ADCDIV = 1;	// ADCx Clock Divisor, Divide by 2, 50Mhz
    ADC3TIMEbits.SAMC = 1;	// 3 TAD
    ADC3TIMEbits.SELRES = 0;	// ADC3 6bit resolution mode
    ADCTRG1bits.TRGSRC3 = 6;	// Set ADC3 to trigger from TMR3
    ADCANCONbits.ANEN3 = 1;	// Enable ADC3 analog bias/logic
    ADCCON3bits.DIGEN3 = 1;	// Enable ADC3 digital logic     
    ADCGIRQEN1bits.AGIEN3 = 1;	//Enb ADC3 AN3 interrupts for DMA

    ADCCON1bits.ON = 1;        		// Turn the ADC on

    // Waiting for ADC warm-up time and ADC bandgap reference to stabilize
    while(!ADCCON2bits.BGVRRDY);	// Wait until the reference voltage is ready
    while(!ADCANCONbits.WKRDY0); 	// Wait until ADC0 is ready
    while(!ADCANCONbits.WKRDY1); 	// Wait until ADC1 is ready
    while(!ADCANCONbits.WKRDY2);    // Wait until ADC2 is ready
    while(!ADCANCONbits.WKRDY3);    // Wait until ADC3 is ready

    ADCDATA0;   // Read ADC data to make sure that data ready bits are clear.
    ADCDATA1;   //
    ADCDATA2;   //
    ADCDATA3;   //
        
    init_DMA();		//Initialize DMA
    init_TMR3();	//Initialize and enable ADC interleaved triggers
}

void init_DMA(void)
{
    // ADC_DATA_VECTOR begins a DMA transfer.
    DCH0ECONbits.CHSIRQ = ADC3_IRQ; //DMA_TRIGGER_ADC3_DATA3;
	DCH0ECONbits.SIRQEN = 1;	//DMA Chan_0 Start IRQ Enable

    // Set DMA Source Starting Address
    DCH0SSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&ADCDATA0);

    // Set DMA Source Size in bytes
    DCH0SSIZ = 16;  //ADC0 + ADC1 + ADC2 + ADC3 = 16bytes

    // Set DMA Destination Starting Address
    DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufA[0]);

    // Set DMA Destination Size
	// (uint16_t) INTERLEAVED_ADC_COUNT*(ADC_DMA_BUFF_SIZE)*sizeof(adc_bufA[0]);
    DCH0DSIZ = (uint16_t) 4*(ADC_DMA_BUFF_SIZE)*sizeof(adc_bufA[0]);

    // Set Cell Size
    DCH0CSIZ = (uint16_t) sizeof(adc_bufA[0]);

    DCH0INTbits.CHDDIF = 0;	//Clr Chan Dest Done Int Flg
    DCH0INTbits.CHDDIE = 1;	//Enable DMA Destination Interrupt
    
    // Enable DMA channel 0
    DCH0CONbits.CHEN = 1;	//DMA Chan 0 enable

    IFS4bits.DMA0IF = 0;	//Clr DMA Chan0 int flg
    IPC33bits.DMA0IP = 7;	//Set DMA Chan0 int priority 7
    IPC33bits.DMA0IS = 3;	//Set DMA Chan0 sub priority 3
    IEC4bits.DMA0IE = 1;	//Enable DMA Chan0 interrupt
    
    DMACONbits.ON = 1;	//Enb DMA
}

void init_TMR3(void)
{
    PR3 = T3_ADC_TRIG;		//ADC3 TRM3 Trigger throughput rate
    
    // ADC0 Trigger setup:
    // TMR3 = OC1 time base, continuous pulse 
    CFGCONbits.OCACLK = 0;	//
    OC1CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC1 module
    OC1CONbits.OCM = 5; 	//Init OC1 low; gen continuous output pulses
    OC1R = OC1_ADC_TRIG;	//ADC0 OC1 Trigger throughput rate
    OC1RS = OC1_ADC_TRIG+2;
    OC1CONSET = 0x8000;		// Enable OC1

    // ADCx Trigger setup:
    // TMR3 = OC3 time base, continuous pulse 
    OC3CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC3 module
    OC3CONbits.OCM = 5; 	//Init OC3 low; gen continuous output pulses
    OC3R = OC3_ADC_TRIG;	//ADC1 OC3 Trigger throughput rate
    OC3RS  = OC3_ADC_TRIG+2;
    OC3CONSET = 0x8000;	// Enable OC3

    // ADCy Trigger setup:
    // TMR3 = OC5 time base, continuous pulse 
    OC5CONbits.OCTSEL = 1;	//Timer"y" is clk source for OC5 module
    OC5CONbits.OCM = 5; 	//Init OC5 low; gen continuous output pulses
    OC5R = OC5_ADC_TRIG;	//ADC2 OC5 Trigger throughput rate
    OC5RS  = OC5_ADC_TRIG+2;
    OC5CONSET = 0x8000;	// Enable OC5
    T3CONSET = 0x8000;		//Start TMR3

}

void __attribute__((interrupt(ipl7auto), vector(_DMA0_VECTOR), aligned(16), nomips16)) isr ()
{
    IFS4bits.DMA0IF = 0;	//Clr DMA Chan 0 int flg
    DCH0INTbits.CHDDIF = 0;	//Clr DMA dest done flg

    adc_dma_buf_full_flg = 1;	//Current DMA buffer is full

    if(adc_buf_index == 0)	//if "adc_bufA" full, change DMA dest to "adc_bufB"
    {
        DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufB[0]);
        adc_buf_index = 1; 
    }
    else			//if "adc_bufB" full, change DMA dest to "adc_bufA"
    {
        DCH0DSA = (uint32_t) VirtAddr_TO_PhysAddr((const void *)&adc_bufA[0]);
        adc_buf_index = 0; 
    }
    DCH0CONbits.CHEN = 1;	//DMA Chan 0 enable
}