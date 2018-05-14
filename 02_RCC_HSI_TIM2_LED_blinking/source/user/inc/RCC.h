#ifndef RCC_H
#define RCC_H


#include "stm32f1xx.h"
#include "system_stm32f1xx.h"


/******************************************************************************/
/* Exported functions *********************************************************/
/******************************************************************************/
void SystemClock_Init(void);

uint32_t GetHCLKFrequency(void);
uint32_t GetPCLK1Frequency(void);
uint32_t GetPCLK2Frequency(void);

void StupidDelay_us(volatile uint32_t delay);
void StupidDelay_ms(volatile uint32_t delay);


#endif /* RCC_H */
