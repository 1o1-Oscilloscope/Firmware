// Code from Microchip AN2785: http://www.microchip.com//wwwAppNotes/AppNotes.aspx?appnote=en607308

#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TAD_TRIGGER_SOURCE_SPACING 2.5 // 2.5
#define ADC_DMA_BUFF_SIZE      4096
	
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
uint32_t __attribute__((coherent)) adc_buf[ADC_DMA_BUFF_SIZE * 5];
uint32_t *adc_bufA = &adc_buf[ADC_DMA_BUFF_SIZE * 0];
uint32_t *adc_bufB = &adc_buf[ADC_DMA_BUFF_SIZE * 1];
uint32_t *adc_bufC = &adc_buf[ADC_DMA_BUFF_SIZE * 2];
uint32_t *adc_bufD = &adc_buf[ADC_DMA_BUFF_SIZE * 3];
uint32_t *adc_bufE = &adc_buf[ADC_DMA_BUFF_SIZE * 4];

uint8_t adc_buf_index = 0;
uint8_t adc_trigger_index = 3;

bool data_ready = false;

void init_ADC(void);
void init_DMA(void);
void init_TMR3(void);
void init_comparator(void);
void reset_trigger(void);
void set_comp_level(uint16_t level);
void set_trig_level(uint8_t level);
void get_adc_data(uint8_t *buff, uint32_t decimation);
	
#ifdef __cplusplus
}
#endif

#endif
