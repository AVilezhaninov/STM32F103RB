/* CMSIS */
#include "CMSIS\Device\stm32f103xb.h"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

/* User */
#include "user\RCC.h"

/******************************************************************************/
/* Private definitions ********************************************************/
/******************************************************************************/
#define LED_TOGGLE_DELAY    500u

/******************************************************************************/
/* Private function prototypes ************************************************/
/******************************************************************************/
static void InitAll();
static void InitHardware();
static void InitGpio();
static void InitRTOSObjects();
static void ToggleLed();

/******************************************************************************/
/* Tasks **********************************************************************/
/******************************************************************************/
void LedTask(void *pvParameters) {
  (void)pvParameters;

  while (1) {
    ToggleLed();
    vTaskDelay(LED_TOGGLE_DELAY);
  }
}

/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main() {
  InitAll();
  vTaskStartScheduler();

  while (1) {
    ;
  }
}

/******************************************************************************/
/* Static functions ***********************************************************/
/******************************************************************************/
static void InitAll() {
  InitHardware();
  InitRTOSObjects();
}

static void InitHardware() {
  rcc::InitSystemClock();
  InitGpio();
}

static void InitGpio(void) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* Enable GPIOC clock */

  /* GPIOC pin 8 in push-pull mode */
  GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* Output push-pull mode */
  GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */
}

static void InitRTOSObjects(void) {
  /* Create tasks */
  xTaskCreate(LedTask, "", configMINIMAL_STACK_SIZE, NULL, 1u, NULL);
}

static void ToggleLed(void) {
  GPIOC->ODR ^= GPIO_ODR_ODR8;        /* Toggle GPIOC pin 8 */
}
