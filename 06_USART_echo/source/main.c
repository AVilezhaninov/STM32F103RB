/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define UART_BAUDRATE       115200
#define UART_IRQ_PRIORITY   5u


/******************************************************************************/
/* Private function prototypes ************************************************/
/******************************************************************************/
static void USART_Init(void);


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * USART3 interrupt handler
 */
void USART3_IRQHandler(void) {
    uint8_t received_data;

    if ((USART3->SR & USART_SR_RXNE) == USART_SR_RXNE) {
        received_data = USART3->DR;     /* Receive data */
        USART3->DR = received_data;     /* Send it back */
    }
}

/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    SystemClock_Init();
    USART_Init();

    while (1) {

    }
}


/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void USART_Init(void) {
    uint32_t APB1_frequency;
    float mantissa;
    uint32_t fraction;

    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;   /* Enable USART3 clock */
    USART3->CR1 |= USART_CR1_RE;            /* Receive enable */
    USART3->CR1 |= USART_CR1_TE;            /* Transmit enable */
    USART3->CR1 |= USART_CR1_RXNEIE;        /* Receive interrupt enable */

    /* Set baud rate */
    APB1_frequency = GetPCLK1Frequency();
    mantissa = APB1_frequency / (16.0f * UART_BAUDRATE);
    fraction = (uint32_t)((mantissa - (uint32_t)mantissa) * 16u);
    USART3->BRR = (USART_BRR_DIV_Mantissa & ((uint32_t)mantissa << 4u)) |
                  (USART_BRR_DIV_Fraction & fraction);

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;     /* Enable PORTB clock */
    GPIOB->CRH |= GPIO_CRH_MODE10_0;        /* Output mode 10 Mhz */
    GPIOB->CRH &= ~GPIO_CRH_CNF10;          /* Clear port configuration */
    GPIOB->CRH |= GPIO_CRH_CNF10_1;         /* Alternate function push-pull */

    NVIC_SetPriority(USART3_IRQn, UART_IRQ_PRIORITY);   /* Set USART3 interrupt
                                                         * priority */
    NVIC_EnableIRQ(USART3_IRQn);            /* Enable USART3 interrupt */

    USART3->CR1 |= USART_CR1_UE;            /* Enable USART3 */
}