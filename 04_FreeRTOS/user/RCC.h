#ifndef RCC_H_
#define RCC_H_

#include "CMSIS\Device\stm32f1xx.h"
#include "CMSIS\Device\system_stm32f1xx.h"

namespace rcc {

/******************************************************************************/
/* Exported functions prototypes **********************************************/
/******************************************************************************/
void InitSystemClock();

uint32_t GetHCLKFrequency();
uint32_t GetPCLK1Frequency();
uint32_t GetPCLK2Frequency();

void StupidDelay_us(volatile uint32_t delay);
void StupidDelay_ms(volatile uint32_t delay);

} /* namespace rcc */

#endif /* RCC_H_ */
