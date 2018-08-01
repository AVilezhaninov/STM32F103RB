/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define USART1_BAUDRATE       115200u
#define USART1_IRQ_PRIORITY   5u

#define USART2_BAUDRATE       115200u
#define USART2_IRQ_PRIORITY   5u

#define USART3_BAUDRATE       115200u
#define USART3_IRQ_PRIORITY   5u


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void USART1_Init(const uint32_t baudrate, const uint32_t irq_priority);
static void USART2_Init(const uint32_t baudrate, const uint32_t irq_priority);
static void USART3_Init(const uint32_t baudrate, const uint32_t irq_priority);
static void SetUsartBaudRate(USART_TypeDef *const usart,
                             const uint32_t baudrate);


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * USART1 interrupt handler
 * Receive data from USART1 and send it back.
 */
void USART1_IRQHandler(void) {
    uint8_t received_data;

    if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE) {
        received_data = USART1->DR;     /* Receive data */
        USART1->DR = received_data;     /* Send it back */
    }
}


/**
 * USART2 interrupt handler
 * Receive data from USART2 and send it back.
 */
void USART2_IRQHandler(void) {
    uint8_t received_data;

    if ((USART2->SR & USART_SR_RXNE) == USART_SR_RXNE) {
        received_data = USART2->DR;     /* Receive data */
        USART2->DR = received_data;     /* Send it back */
    }
}


/**
 * USART3 interrupt handler
 * Receive data from USART3 and send it back.
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
    USART1_Init(USART1_BAUDRATE, USART1_IRQ_PRIORITY);
    USART2_Init(USART2_BAUDRATE, USART2_IRQ_PRIORITY);
    USART3_Init(USART3_BAUDRATE, USART3_IRQ_PRIORITY);

    while (1) {

    }
}




/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
/**
 * Init USART1
 * PA9->Tx, PA10->Rx
 */
static void USART1_Init(const uint32_t baudrate, const uint32_t irq_priority) {
    /* Init USART1 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;     /* Enable PORTA clock */
    GPIOA->CRH |= GPIO_CRH_MODE9_0;         /* Output mode 10 MHz */
    GPIOA->CRH &= ~GPIO_CRH_CNF9;           /* Clear port configuration */
    GPIOA->CRH |= GPIO_CRH_CNF9_1;          /* Alternate function push-pull */

    /* Init USART1 */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;   /* Enable USART1 clock */
    USART1->CR1 |= USART_CR1_RE;            /* Receive enable */
    USART1->CR1 |= USART_CR1_TE;            /* Transmit enable */
    USART1->CR1 |= USART_CR1_RXNEIE;        /* Receive interrupt enable */
    SetUsartBaudRate(USART1, baudrate);     /* Set baud rate */

    NVIC_SetPriority(USART1_IRQn, irq_priority); /* Set USART1 IRQ priority */
    NVIC_EnableIRQ(USART1_IRQn);                 /* Enable USART1 interrupt */

    USART1->CR1 |= USART_CR1_UE;            /* Enable USART1 */
}


/**
 * Init USART2
 * PA2->Tx, PA3->Rx
 */
static void USART2_Init(const uint32_t baudrate, const uint32_t irq_priority) {
    /* Init USART2 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;     /* Enable PORTA clock */
    GPIOA->CRL |= GPIO_CRL_MODE2_0;         /* Output mode 10 MHz */
    GPIOA->CRL &= ~GPIO_CRL_CNF2;           /* Clear port configuration */
    GPIOA->CRL |= GPIO_CRL_CNF2_1;          /* Alternate function push-pull */

    /* Init USART2 */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;   /* Enable USART2 clock */
    USART2->CR1 |= USART_CR1_RE;            /* Receive enable */
    USART2->CR1 |= USART_CR1_TE;            /* Transmit enable */
    USART2->CR1 |= USART_CR1_RXNEIE;        /* Receive interrupt enable */
    SetUsartBaudRate(USART2, baudrate);     /* Set baud rate */

    NVIC_SetPriority(USART2_IRQn, irq_priority); /* Set USART2 IRQ priority */
    NVIC_EnableIRQ(USART2_IRQn);                 /* Enable USART2 interrupt */

    USART2->CR1 |= USART_CR1_UE;            /* Enable USART2 */
}


/**
 * Init USART3
 * PB10->Tx, PB11->Rx
 */
static void USART3_Init(const uint32_t baudrate, const uint32_t irq_priority) {
    /* Init USART3 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;     /* Enable PORTB clock */
    GPIOB->CRH |= GPIO_CRH_MODE10_0;        /* Output mode 10 MHz */
    GPIOB->CRH &= ~GPIO_CRH_CNF10;          /* Clear port configuration */
    GPIOB->CRH |= GPIO_CRH_CNF10_1;         /* Alternate function push-pull */

    /* Init USART3 */
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;   /* Enable USART3 clock */
    USART3->CR1 |= USART_CR1_RE;            /* Receive enable */
    USART3->CR1 |= USART_CR1_TE;            /* Transmit enable */
    USART3->CR1 |= USART_CR1_RXNEIE;        /* Receive interrupt enable */
    SetUsartBaudRate(USART3, baudrate);     /* Set baud rate */

    NVIC_SetPriority(USART3_IRQn, irq_priority); /* Set USART3 IRQ priority */
    NVIC_EnableIRQ(USART3_IRQn);                 /* Enable USART3 interrupt */

    USART3->CR1 |= USART_CR1_UE;            /* Enable USART3 */
}


/**
 * Set USART baud rate
 * @param usart    USART instance
 * @param baudrate Required baud rate
 */
static void SetUsartBaudRate(USART_TypeDef *const usart,
                             const uint32_t baudrate) {
    uint32_t bus_clock;
    float mantissa;
    uint32_t fraction;

    /* Get bus clock for current USART */
    if (usart == USART1) {
        bus_clock = GetPCLK2Frequency();
    } else {
        bus_clock = GetPCLK1Frequency();
    }

    /* Set baud rate */
    mantissa = bus_clock / (16.0f * baudrate);
    fraction = (uint32_t)((mantissa - (uint32_t)mantissa) * 16u);
    usart->BRR = (USART_BRR_DIV_Mantissa & ((uint32_t)mantissa << 4u)) |
                 (USART_BRR_DIV_Fraction & fraction);
}
