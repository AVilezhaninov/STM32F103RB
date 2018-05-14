/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
/* TIM2 prescaler and auto reload values */
#define TIM2_PSC            3299u
#define TIM2_ARR            9999u
#define TIM2_IRQ_PRIORITY   1u


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * TIM2 interrupt handler
 */
void TIM2_IRQHandler(void) {
    /* Clear TIM2 update interrupt flag */
    TIM2->SR &= ~TIM_SR_UIF;
    /* Toggle LED */
    GPIOC->ODR ^= GPIO_ODR_ODR8;
}


/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Init system clock with HSI and PLL for 64 MHz */
    SystemClock_Init();
  
    /* Enable GPIOC clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* enable GPIOC clock*/
    /* GPIOC pin 8 in push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* output push-pull mode */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* output mode 2 Mhz */

    /* Enable TIM2 clock */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    /* Set TIM2 prescaler */
    TIM2->PSC = TIM2_PSC;
    /* Set TIM2 auto reload value */
    TIM2->ARR = TIM2_ARR;
    /* Enable TIM2 update interrupt */
    TIM2->DIER |= TIM_DIER_UIE;
    /* Set TIM2 interrupt priority */
    NVIC_SetPriority(TIM2_IRQn, TIM2_IRQ_PRIORITY);
    /* Enable TIM2 interrupt */
    NVIC_EnableIRQ(TIM2_IRQn);
    /* Enable TIM2 timer */
    TIM2->CR1 |= TIM_CR1_CEN;
    
    while (1) {

    }
}
