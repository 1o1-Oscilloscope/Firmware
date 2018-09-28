// Code from Microchip AN2785: http://www.microchip.com//wwwAppNotes/AppNotes.aspx?appnote=en607308

#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TAD_TRIGGER_SOURCE_SPACING 2.5
#define ADC_DMA_BUFF_SIZE      1024
	
#define ADC_TRIG        (TAD_TRIGGER_SOURCE_SPACING * 2)
#define OC1_ADC_TRIG    (ADC_TRIG - 1)
#define OC3_ADC_TRIG    ((2 * ADC_TRIG) - 1)
#define OC5_ADC_TRIG    ((3 * ADC_TRIG) - 1)
// ((INTERLEAVED_ADC_COUNT * ADC_TRIG) - 1)
#define T3_ADC_TRIG     ((4 * ADC_TRIG) - 1)

#define ADC0_IRQ	59	//PIC32MZxxEFxx ADC0 Data_0 IRQ number
#define ADC1_IRQ	60	//PIC32MZxxEFxx ADC1 Data_1 IRQ number
#define ADC2_IRQ	61	//PIC32MZxxEFxx ADC2 Data_2 IRQ number
#define ADC3_IRQ	62	//PIC32MZxxEFxx ADC3 Data_3 IRQ number

#define VirtAddr_TO_PhysAddr(v) ((unsigned long)(v) & 0x1FFFFFFF)

// [INTERLEAVED_ADC_COUNT * ADC_DMA_BUFF_SIZE]
uint32_t __attribute__((coherent)) adc_bufA[4 * ADC_DMA_BUFF_SIZE];
uint32_t __attribute__((coherent)) adc_bufB[4 * ADC_DMA_BUFF_SIZE];
uint32_t adc_buf_index = 0;
bool adc_dma_buf_full_flg = 0;

void init_ADC(void);
void init_DMA(void);
void init_TMR3(void);
	
#ifdef __cplusplus
}
#endif

#endif
