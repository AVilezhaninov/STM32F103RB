/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
/* TIM1 */
#define TIM1_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM1_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM1_IRQ_PRIORITY   5u

/* TIM2 */
#define TIM2_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM2_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM2_IRQ_PRIORITY   5u

/* TIM3 */
#define TIM3_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM3_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM3_IRQ_PRIORITY   5u

/* TIM4 */
#define TIM4_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM4_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM4_IRQ_PRIORITY   5u


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void TIM1_Init(void);
static void TIM2_Init(void);
static void TIM3_Init(void);
static void TIM4_Init(void);


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * TIM1 interrupt handler
 */
void TIM1_UP_IRQHandler(void) {
    TIM1->SR &= ~TIM_SR_UIF;    /* Clear TIM1 update interrupt flag */

    /* Do something here */
}


/**
 * TIM2 interrupt handler
 */
void TIM2_IRQHandler(void) {
    TIM2->SR &= ~TIM_SR_UIF;    /* Clear TIM2 update interrupt flag */

    /* Do something here */
}


/**
 * TIM3 interrupt handler
 */
void TIM3_IRQHandler(void) {
    TIM3->SR &= ~TIM_SR_UIF;    /* Clear TIM3 update interrupt flag */

    /* Do something here */
}


/**
 * TIM4 interrupt handler
 */
void TIM4_IRQHandler(void) {
    TIM4->SR &= ~TIM_SR_UIF;    /* Clear TIM4 update interrupt flag */

    /* Do something here */
}




/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    SystemClock_Init();
    TIM1_Init();
    TIM2_Init();
    TIM3_Init();
    TIM4_Init();

    while (1) {

    }
}




/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void TIM1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;     /* Enable TIM1 clock */
    TIM1->PSC = TIM1_PSC;                   /* Set prescaler */
    TIM1->ARR = TIM1_ARR;                   /* Set auto reload value */
    TIM1->DIER |= TIM_DIER_UIE;             /* Enable update interrupt */
    NVIC_SetPriority(TIM1_UP_IRQn, TIM1_IRQ_PRIORITY);/* Set IRQ priority */
    NVIC_EnableIRQ(TIM1_UP_IRQn);                     /* Enable interrupt */
    TIM1->CR1 |= TIM_CR1_CEN;               /* Enable timer */
}


static void TIM2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     /* Enable TIM2 clock */
    TIM2->PSC = TIM2_PSC;                   /* Set prescaler */
    TIM2->ARR = TIM2_ARR;                   /* Set auto reload value */
    TIM2->DIER |= TIM_DIER_UIE;             /* Enable update interrupt */
    NVIC_SetPriority(TIM2_IRQn, TIM2_IRQ_PRIORITY); /* Set IRQ priority */
    NVIC_EnableIRQ(TIM2_IRQn);                      /* Enable interrupt */
    TIM2->CR1 |= TIM_CR1_CEN;               /* Enable timer */
}


static void TIM3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     /* Enable TIM3 clock */
    TIM3->PSC = TIM3_PSC;                   /* Set prescaler */
    TIM3->ARR = TIM3_ARR;                   /* Set auto reload value */
    TIM3->DIER |= TIM_DIER_UIE;             /* Enable update interrupt */
    NVIC_SetPriority(TIM3_IRQn, TIM3_IRQ_PRIORITY); /* Set IRQ priority */
    NVIC_EnableIRQ(TIM3_IRQn);                      /* Enable interrupt */
    TIM3->CR1 |= TIM_CR1_CEN;               /* Enable timer */
}


static void TIM4_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;     /* Enable TIM4 clock */
    TIM4->PSC = TIM4_PSC;                   /* Set prescaler */
    TIM4->ARR = TIM4_ARR;                   /* Set auto reload value */
    TIM4->DIER |= TIM_DIER_UIE;             /* Enable update interrupt */
    NVIC_SetPriority(TIM4_IRQn, TIM4_IRQ_PRIORITY); /* Set IRQ priority */
    NVIC_EnableIRQ(TIM4_IRQn);                      /* Enable interrupt */
    TIM4->CR1 |= TIM_CR1_CEN;               /* Enable timer */
}
