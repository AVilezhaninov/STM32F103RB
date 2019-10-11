/* CMSIS */
#include "CMSIS\Device\stm32f103xb.h"

/******************************************************************************/
/* Private definitions ********************************************************/
/******************************************************************************/
#define LED_TOGGLE_DELAY 1000000u

/******************************************************************************/
/* Private function prototypes ************************************************/
/******************************************************************************/
static void InitGpio();
static void ToggleLed();
static void DummyDelay(volatile int delay);

/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main() {
  InitGpio();

  while (1) {
    ToggleLed();
    DummyDelay(LED_TOGGLE_DELAY);
  }
}

/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void InitGpio() {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* Enable GPIO clock */

  /* GPIOC pin 8 in push-pull mode */
  GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* Output push-pull mode */
  GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */
}

static void ToggleLed() {
  GPIOC->ODR ^= GPIO_ODR_ODR8;        /* Toggle GPIOC pin 8 */
}

static void DummyDelay(volatile int delay) {
  while (delay-- > 0) {
    ;
  }
}
