/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
/* TIM3 constants */
#define TIM3_PSC  (7200u - 1u)  /* TIM3 clock: (72 MHz / 7200) = 10 kHz */
#define TIM3_ARR  (10000u - 1u) /* TIM3 PWM period: (10 kHz / 10000) = 1 Hz */
#define TIM3_CCR3 (5000u - 1u)  /* TIM3 PWM duty cycle: (10kHz / 5000)=0.5 Hz */


/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Init system clock with HSE and PLL for 72 MHz */
    SystemClock_Init();
  
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* enable GPIOC clock*/
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; /* enable AFIO clock*/
    
    /* Remap TIM3 */
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP;
    
    /* GPIOC pin 8 in alternate push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* Clear configurations bits */
    GPIOC->CRH |= GPIO_CRH_CNF8_1;      /* AF output push-pull */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 Mhz */

    /* TIM3 PWM init */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; /* Enable TIM3 clock */
    TIM3->PSC = TIM3_PSC;               /* Set TIM3 prescaler */
    TIM3->ARR = TIM3_ARR;               /* Set TIM3 auto reload value */
    TIM3->CCR3 = TIM3_CCR3;             /* Set TIM3 compare value */
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; /* Set PWM mode */
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;     /* Preload register enable */
    TIM3->CCER |= TIM_CCER_CC3E;        /* Enable signal output */
    TIM3->CR1 |= TIM_CR1_ARPE;          /* Auto-reload preload enable */
    TIM3->CR1 |= TIM_CR1_CEN;           /* Enable TIM3 timer */
    
    while (1) {

    }
}
