/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Private function prototypes ************************************************/
/******************************************************************************/
static void SPI1_Init(void);
static void CSSet(void);
static void CSReset(void);


/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    /* Data to send through SPI */
    uint8_t spi_data = 0u;

    SystemClock_Init();
    SPI1_Init();

    while (1) {
        /* Set chip select low */
        CSReset();

        /* Send data through SPI */
        SPI1->DR = spi_data;
        /* Wait till data come back */
        while ((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE) {
            ;
        }
        /* Read received data */
        spi_data = SPI1->DR;

        /* Set chip select high */
        CSSet();

        ++spi_data;
    }
}


/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void SPI1_Init(void) {
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* enable GPIOA clock*/

    /* SPI1 SCK pin init */
    GPIOA->CRL &= ~GPIO_CRL_CNF5;       /* clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF5_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE5;       /* output mode 50 Mhz */

    /* SPI1 MISO pin init in AF mode */
    GPIOA->CRL &= ~GPIO_CRL_CNF6;       /* clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF6_0;      /* floating input */
    GPIOA->CRL &= ~GPIO_CRL_MODE6;      /* input mode */

    /* SPI1 MOSI pin init */
    GPIOA->CRL &= ~GPIO_CRL_CNF7;       /* clear bits */
    GPIOA->CRL |= GPIO_CRL_CNF7_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE7;       /* output mode 50 Mhz */

    /* GPIOA pin 8 in push-pull mode */
    GPIOA->CRH &= ~GPIO_CRH_CNF8;       /* output push-pull mode */
    GPIOA->CRH |= GPIO_CRH_MODE8_0;     /* output mode 10 Mhz */

    /* SPI1 init */
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; /* enable SPI1 clock */
    SPI1->CR1 &= ~SPI_CR1_BR_0;         /* Fpclk/2 */
    SPI1->CR1 |= SPI_CR1_MSTR;          /* SPI in master mode */
    SPI1->CR1 |= SPI_CR1_SSM;           /* SSM = 1 */
    SPI1->CR1 |= SPI_CR1_SSI;           /* SSI = 1 */
    SPI1->CR2 |= SPI_CR2_RXNEIE;        /* Rx interrupt enable */
    SPI1->CR1 |= SPI_CR1_SPE;           /* Enable SPI */
}


static void CSSet(void) {
    GPIOA->BSRR |= GPIO_BSRR_BS8;
}


static void CSReset(void) {
    GPIOA->BSRR |= GPIO_BSRR_BR8;
}