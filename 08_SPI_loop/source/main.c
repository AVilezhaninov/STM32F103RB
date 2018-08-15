/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define SPI1_IRQ_PRIORITY   5u
#define SPI2_IRQ_PRIORITY   5u


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void SPI1_Init(void);
static void SPI1_CSSet(void);
static void SPI1_CSReset(void);

static void SPI2_Init(void);
static void SPI2_CSSet(void);
static void SPI2_CSReset(void);


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
void SPI1_IRQHandler(void) {
    uint8_t received_data;

    if ((SPI1->SR & SPI_SR_RXNE) == SPI_SR_RXNE) {
        received_data = SPI1->DR;

        SPI1_CSSet();
    }
}


void SPI2_IRQHandler(void) {
    uint8_t received_data;

    if ((SPI2->SR & SPI_SR_RXNE) == SPI_SR_RXNE) {
        received_data = SPI2->DR;

        SPI2_CSSet();
    }
}



/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Data to send through SPI */
    uint8_t spi_data = 0u;

    SystemClock_Init();
    SPI1_Init();
    SPI2_Init();

    while (1) {
        SPI1_CSReset();
        SPI1->DR = spi_data;    /* Send data through SPI1 */

        SPI2_CSReset();
        SPI2->DR = spi_data;    /* Send data through SPI2 */


        ++spi_data;
        StupidDelay_ms(10u);
    }
}


/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void SPI1_Init(void) {
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* Enable GPIOA clock */

    /* SPI1 SCK pin init */
    GPIOA->CRL &= ~GPIO_CRL_CNF5;       /* Clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF5_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE5;       /* Output mode 50 Mhz */

    /* SPI1 MISO pin init in AF mode */
    GPIOA->CRL &= ~GPIO_CRL_CNF6;       /* Clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF6_0;      /* Floating input */
    GPIOA->CRL &= ~GPIO_CRL_MODE6;      /* Input mode */

    /* SPI1 MOSI pin init */
    GPIOA->CRL &= ~GPIO_CRL_CNF7;       /* Clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF7_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE7;       /* Output mode 50 Mhz */

    /* GPIOA pin 8 in push-pull mode */
    GPIOA->CRH &= ~GPIO_CRH_CNF8;       /* Output push-pull mode */
    GPIOA->CRH |= GPIO_CRH_MODE8_0;     /* Output mode 10 Mhz */

    /* SPI2 init */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; /* Enable SPI1 clock */
    SPI1->CR1 &= ~SPI_CR1_BR_0;         /* Fpclk/2 */
    SPI1->CR1 |= SPI_CR1_MSTR;          /* SPI in master mode */
    SPI1->CR1 |= SPI_CR1_SSM;           /* SSM = 1 */
    SPI1->CR1 |= SPI_CR1_SSI;           /* SSI = 1 */
    SPI1->CR2 |= SPI_CR2_RXNEIE;        /* Rx interrupt enable */

    NVIC_SetPriority(SPI1_IRQn, SPI1_IRQ_PRIORITY); /* Set IRQ priority */
    NVIC_EnableIRQ(SPI1_IRQn);                      /* Enable interrupt */

    SPI1->CR1 |= SPI_CR1_SPE;           /* Enable SPI */
}


static void SPI1_CSSet(void) {
    GPIOA->BSRR |= GPIO_BSRR_BS8;
}


static void SPI1_CSReset(void) {
    GPIOA->BSRR |= GPIO_BSRR_BR8;
}


static void SPI2_Init(void) {
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; /* Enable GPIOB clock */

    /* SPI2 SCK pin init */
    GPIOB->CRH &= ~GPIO_CRH_CNF13;      /* Clear bits */
    GPIOB->CRH |= GPIO_CRH_CNF13_1;     /* AF output push-pull */
    GPIOB->CRH |= GPIO_CRH_MODE13;      /* Output mode 50 Mhz */

    /* SPI2 MISO pin init in AF mode */
    GPIOB->CRH &= ~GPIO_CRH_CNF14;      /* Clear bits */
    GPIOB->CRH |= GPIO_CRH_CNF14_0;     /* Floating input */
    GPIOB->CRH &= ~GPIO_CRH_MODE14;     /* Input mode */

    /* SPI2 MOSI pin init */
    GPIOB->CRH &= ~GPIO_CRH_CNF15;      /* Clear bits */
    GPIOB->CRH |= GPIO_CRH_CNF15_1;     /* AF output push-pull */
    GPIOB->CRH |= GPIO_CRH_MODE15;      /* Output mode 50 Mhz */

    /* GPIOB pin 12 in push-pull mode */
    GPIOB->CRH &= ~GPIO_CRH_CNF12;      /* Output push-pull mode */
    GPIOB->CRH |= GPIO_CRH_MODE12_0;    /* Output mode 10 Mhz */

    /* SPI2 init */
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; /* Enable SPI2 clock */
    SPI2->CR1 &= ~SPI_CR1_BR_0;         /* Fpclk/2 */
    SPI2->CR1 |= SPI_CR1_MSTR;          /* SPI in master mode */
    SPI2->CR1 |= SPI_CR1_SSM;           /* SSM = 1 */
    SPI2->CR1 |= SPI_CR1_SSI;           /* SSI = 1 */
    SPI2->CR2 |= SPI_CR2_RXNEIE;        /* Rx interrupt enable */

    NVIC_SetPriority(SPI2_IRQn, SPI2_IRQ_PRIORITY); /* Set IRQ priority */
    NVIC_EnableIRQ(SPI2_IRQn);                      /* Enable interrupt */

    SPI2->CR1 |= SPI_CR1_SPE;           /* Enable SPI */
}


static void SPI2_CSSet(void) {
    GPIOB->BSRR |= GPIO_BSRR_BS12;
}


static void SPI2_CSReset(void) {
    GPIOB->BSRR |= GPIO_BSRR_BR12;
}
