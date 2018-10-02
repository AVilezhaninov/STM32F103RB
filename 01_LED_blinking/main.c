/* CMSIS */
#include "stm32f103xb.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define LED_TOGGLE_DELAY    500000u


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void GPIO_Init(void);
static void ToggleLed(void);
static void DummyDelay(const int delay);




/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    GPIO_Init();

    while (1) {
        ToggleLed();
        DummyDelay(LED_TOGGLE_DELAY);
    }
}




/******************************************************************************/
/* Static functions ***********************************************************/
/******************************************************************************/
static void GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* Enable GPIOC clock */

    /* GPIOC pin 8 in push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* Output push-pull mode */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */
}


static void ToggleLed(void) {
    GPIOC->ODR ^= GPIO_ODR_ODR8;        /* Toggle GPIOC pin 8 */
}


static void DummyDelay(const int delay) {
    for (volatile int i = 0; i < delay; ++i) {
        ;
    }
}
