/* CMSIS */
#include "stm32f103xb.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define LED_TOGGLE_DELAY    160000u


/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Enable GPIOC clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* enable GPIOC clock*/
  
    /* GPIOC pin 8 in push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* output push-pull mode */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* output mode 2 Mhz */

    while (1) {
        /* Toggle GPIOC pin 8 */
        GPIOC->ODR ^= GPIO_ODR_ODR8;
        /* Toggle delay */
        for (volatile int i = 0; i < LED_TOGGLE_DELAY; ++i) {
            ;
        }
    }
}
