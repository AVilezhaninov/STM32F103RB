/* CMSIS */
#include "stm32f103xb.h"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define LED_TOGGLE_DELAY_MS     500u


/******************************************************************************/
/* Tasks **********************************************************************/
/******************************************************************************/
void LEDBlinkTask(void *pvParameters) {
    (void)pvParameters;

    while (1) {
        /* Toggle GPIOC pin 8 */
        GPIOC->ODR ^= GPIO_ODR_ODR8;
        /* Task delay */
        vTaskDelay(LED_TOGGLE_DELAY_MS);
    }
}

/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Init system clock */
    SystemClock_Init();
  
    /* Enable GPIOC clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* enable GPIOC clock*/
  
    /* GPIOC pin 8 in push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* output push-pull mode */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* output mode 2 Mhz */
    
    /* FreeRTOS init */
    /* Create LED blinking task */
    xTaskCreate(LEDBlinkTask, (char const*)"", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY + 1u, NULL);
    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();
    
    while (1) {

    }
}
