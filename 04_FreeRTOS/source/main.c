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
#define LED_TOGGLE_DELAY    500u


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void InitAll(void);
static void InitHardware(void);
static void GPIO_Init(void);
static void InitFreeRTOSObjects(void);
static void ToggleLed(void);


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
int main(void) {
    InitAll();
    vTaskStartScheduler();

    while (1) {

    }
}




/******************************************************************************/
/* Static functions ***********************************************************/
/******************************************************************************/
static void InitAll(void) {
    InitHardware();
    InitFreeRTOSObjects();
}


static void InitHardware(void) {
    SystemClock_Init();
    GPIO_Init();
}


static void GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; /* Enable GPIOC clock */

    /* GPIOC pin 8 in push-pull mode */
    GPIOC->CRH &= ~GPIO_CRH_CNF8;       /* Output push-pull mode */
    GPIOC->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */
}


static void InitFreeRTOSObjects(void) {
    /* Create RTOS tasks */
    xTaskCreate(LedTask, (char const*)"", configMINIMAL_STACK_SIZE,
                NULL, tskIDLE_PRIORITY + 1u, NULL);
}


static void ToggleLed(void) {
    GPIOC->ODR ^= GPIO_ODR_ODR8;        /* Toggle GPIOC pin 8 */
}
