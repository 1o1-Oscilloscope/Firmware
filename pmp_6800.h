/*
 * PMP 6800 Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   pmp_6800.h
 * 
 * @Summary
 *   Interface to operate parallel master port in 6800-series mode.
*/

#ifndef PMP_6800_H    
#define PMP_6800_H

#include <xc.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


void pmp_6800_init();

void    pmp_6800_write_command(uint8_t command);
uint8_t pmp_6800_read_status();
void    pmp_6800_write_data(uint8_t data);
uint8_t pmp_6800_read_data();


#ifdef __cplusplus
}
#endif

#endif /* PMP_6800_H */
