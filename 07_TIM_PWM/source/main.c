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
#define TIM1_CCR1           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM1_CCR2           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM1_CCR3           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM1_CCR4           5000u           /* (10 kHz / 5000) = 2 Hz */

/* TIM2 */
#define TIM2_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM2_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM2_CCR1           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM2_CCR2           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM2_CCR3           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM2_CCR4           5000u           /* (10 kHz / 5000) = 2 Hz */

/* TIM3 */
#define TIM3_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM3_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM3_CCR1           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM3_CCR2           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM3_CCR3           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM3_CCR4           5000u           /* (10 kHz / 5000) = 2 Hz */

/* TIM4 */
#define TIM4_PSC            (7200u - 1u)    /* (72 MHz / 7200) = 10 kHz */
#define TIM4_ARR            (10000u - 1u)   /* (10 kHz / 10000) = 1 Hz */
#define TIM4_CCR1           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM4_CCR2           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM4_CCR3           5000u           /* (10 kHz / 5000) = 2 Hz */
#define TIM4_CCR4           5000u           /* (10 kHz / 5000) = 2 Hz */


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void TIM1_Init(void);
static void TIM2_Init(void);
static void TIM3_Init(void);
static void TIM4_Init(void);




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
    /* Init TIM1 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* Enable GPIOA clock*/

    /* PA8 TIM1_CH1 */
    GPIOA->CRH &= ~GPIO_CRH_CNF8;       /* Clear configurations bits */
    GPIOA->CRH |= GPIO_CRH_CNF8_1;      /* AF output push-pull */
    GPIOA->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */

    /* PA9 TIM1_CH2 */
    GPIOA->CRH &= ~GPIO_CRH_CNF9;       /* Clear configurations bits */
    GPIOA->CRH |= GPIO_CRH_CNF9_1;      /* AF output push-pull */
    GPIOA->CRH |= GPIO_CRH_MODE9_1;     /* Output mode 2 MHz */

    /* PA10 TIM1_CH3 */
    GPIOA->CRH &= ~GPIO_CRH_CNF10;      /* Clear configurations bits */
    GPIOA->CRH |= GPIO_CRH_CNF10_1;     /* AF output push-pull */
    GPIOA->CRH |= GPIO_CRH_MODE10_1;    /* Output mode 2 MHz */

    /* PA11 TIM2_CH4 */
    GPIOA->CRH &= ~GPIO_CRH_CNF11;      /* Clear configurations bits */
    GPIOA->CRH |= GPIO_CRH_CNF11_1;     /* AF output push-pull */
    GPIOA->CRH |= GPIO_CRH_MODE11_1;    /* Output mode 2 MHz */

    /* Init TIM1 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; /* Enable TIM1 clock */
    TIM1->PSC = TIM1_PSC;               /* Set prescaler */
    TIM1->ARR = TIM1_ARR;               /* Set auto reload value */
    TIM1->CCR1 = TIM1_CCR1;             /* Set compare value CH1 */
    TIM1->CCR2 = TIM1_CCR2;             /* Set compare value CH2 */
    TIM1->CCR3 = TIM1_CCR3;             /* Set compare value CH3 */
    TIM1->CCR4 = TIM1_CCR4;             /* Set compare value CH4 */
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; /* Set CH1 PWM mode */
    TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; /* Set CH2 PWM mode */
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; /* Set CH3 PWM mode */
    TIM1->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; /* Set CH4 PWM mode */
    TIM1->CCER |= TIM_CCER_CC1E;        /* Enable signal output CH1 */
    TIM1->CCER |= TIM_CCER_CC2E;        /* Enable signal output CH2 */
    TIM1->CCER |= TIM_CCER_CC3E;        /* Enable signal output CH3 */
    TIM1->CCER |= TIM_CCER_CC4E;        /* Enable signal output CH4 */
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_CEN;           /* Enable timer */
}


static void TIM2_Init(void) {
    /* Init TIM2 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* Enable GPIOA clock*/

    /* PA0 TIM2_CH1 */
    GPIOA->CRL &= ~GPIO_CRL_CNF0;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF0_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE0_1;     /* Output mode 2 MHz */

    /* PA1 TIM2_CH2 */
    GPIOA->CRL &= ~GPIO_CRL_CNF1;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF1_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE1_1;     /* Output mode 2 MHz */

    /* PA2 TIM2_CH3 */
    GPIOA->CRL &= ~GPIO_CRL_CNF2;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF2_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE2_1;     /* Output mode 2 MHz */

    /* PA3 TIM2_CH4 */
    GPIOA->CRL &= ~GPIO_CRL_CNF3;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF3_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE3_1;     /* Output mode 2 MHz */

    /* Init TIM2 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; /* Enable TIM2 clock */
    TIM2->PSC = TIM2_PSC;               /* Set prescaler */
    TIM2->ARR = TIM2_ARR;               /* Set auto reload value */
    TIM2->CCR1 = TIM2_CCR1;             /* Set compare value CH1 */
    TIM2->CCR2 = TIM2_CCR2;             /* Set compare value CH2 */
    TIM2->CCR3 = TIM2_CCR3;             /* Set compare value CH3 */
    TIM2->CCR4 = TIM2_CCR4;             /* Set compare value CH4 */
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; /* Set CH1 PWM mode */
    TIM2->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; /* Set CH2 PWM mode */
    TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; /* Set CH3 PWM mode */
    TIM2->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; /* Set CH4 PWM mode */
    TIM2->CCER |= TIM_CCER_CC1E;        /* Enable signal output CH1 */
    TIM2->CCER |= TIM_CCER_CC2E;        /* Enable signal output CH2 */
    TIM2->CCER |= TIM_CCER_CC3E;        /* Enable signal output CH3 */
    TIM2->CCER |= TIM_CCER_CC4E;        /* Enable signal output CH4 */
    TIM2->CR1 |= TIM_CR1_CEN;           /* Enable timer */
}


static void TIM3_Init(void) {
    /* Init TIM3 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* Enable GPIOA clock*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; /* Enable GPIOB clock*/

    /* PA6 TIM3_CH1 */
    GPIOA->CRL &= ~GPIO_CRL_CNF6;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF6_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE6_1;     /* Output mode 2 MHz */

    /* PA7 TIM3_CH2 */
    GPIOA->CRL &= ~GPIO_CRL_CNF7;       /* Clear configurations bits */
    GPIOA->CRL |= GPIO_CRL_CNF7_1;      /* AF output push-pull */
    GPIOA->CRL |= GPIO_CRL_MODE7_1;     /* Output mode 2 MHz */

    /* PB0 TIM3_CH3 */
    GPIOB->CRL &= ~GPIO_CRL_CNF0;       /* Clear configurations bits */
    GPIOB->CRL |= GPIO_CRL_CNF0_1;      /* AF output push-pull */
    GPIOB->CRL |= GPIO_CRL_MODE0_1;     /* Output mode 2 MHz */

    /* PB1 TIM3_CH4 */
    GPIOB->CRL &= ~GPIO_CRL_CNF1;       /* Clear configurations bits */
    GPIOB->CRL |= GPIO_CRL_CNF1_1;      /* AF output push-pull */
    GPIOB->CRL |= GPIO_CRL_MODE1_1;     /* Output mode 2 MHz */

    /* Init TIM3 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; /* Enable TIM3 clock */
    TIM3->PSC = TIM3_PSC;               /* Set prescaler */
    TIM3->ARR = TIM3_ARR;               /* Set auto reload value */
    TIM3->CCR1 = TIM3_CCR1;             /* Set compare value CH1 */
    TIM3->CCR2 = TIM3_CCR2;             /* Set compare value CH2 */
    TIM3->CCR3 = TIM3_CCR3;             /* Set compare value CH3 */
    TIM3->CCR4 = TIM3_CCR4;             /* Set compare value CH4 */
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; /* Set CH1 PWM mode */
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; /* Set CH2 PWM mode */
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; /* Set CH3 PWM mode */
    TIM3->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; /* Set CH4 PWM mode */
    TIM3->CCER |= TIM_CCER_CC1E;        /* Enable signal output CH1 */
    TIM3->CCER |= TIM_CCER_CC2E;        /* Enable signal output CH2 */
    TIM3->CCER |= TIM_CCER_CC3E;        /* Enable signal output CH3 */
    TIM3->CCER |= TIM_CCER_CC4E;        /* Enable signal output CH4 */
    TIM3->CR1 |= TIM_CR1_CEN;           /* Enable timer */
}


static void TIM4_Init(void) {
    /* Init TIM4 pins */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; /* Enable GPIOB clock*/

    /* PB6 TIM4_CH1 */
    GPIOB->CRL &= ~GPIO_CRL_CNF6;       /* Clear configurations bits */
    GPIOB->CRL |= GPIO_CRL_CNF6_1;      /* AF output push-pull */
    GPIOB->CRL |= GPIO_CRL_MODE6_1;     /* Output mode 2 MHz */

    /* PB7 TIM4_CH2 */
    GPIOB->CRL &= ~GPIO_CRL_CNF7;       /* Clear configurations bits */
    GPIOB->CRL |= GPIO_CRL_CNF7_1;      /* AF output push-pull */
    GPIOB->CRL |= GPIO_CRL_MODE7_1;     /* Output mode 2 MHz */

    /* PB8 TIM4_CH3 */
    GPIOB->CRH &= ~GPIO_CRH_CNF8;       /* Clear configurations bits */
    GPIOB->CRH |= GPIO_CRH_CNF8_1;      /* AF output push-pull */
    GPIOB->CRH |= GPIO_CRH_MODE8_1;     /* Output mode 2 MHz */

    /* PB9 TIM4_CH4 */
    GPIOB->CRH &= ~GPIO_CRH_CNF9;       /* Clear configurations bits */
    GPIOB->CRH |= GPIO_CRH_CNF9_1;      /* AF output push-pull */
    GPIOB->CRH |= GPIO_CRH_MODE9_1;     /* Output mode 2 MHz */

    /* Init TIM4 */
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; /* Enable TIM4 clock */
    TIM4->PSC = TIM4_PSC;               /* Set prescaler */
    TIM4->ARR = TIM4_ARR;               /* Set auto reload value */
    TIM4->CCR1 = TIM4_CCR1;             /* Set compare value CH1 */
    TIM4->CCR2 = TIM4_CCR2;             /* Set compare value CH2 */
    TIM4->CCR3 = TIM4_CCR3;             /* Set compare value CH3 */
    TIM4->CCR4 = TIM4_CCR4;             /* Set compare value CH4 */
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; /* Set CH1 PWM mode */
    TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1; /* Set CH2 PWM mode */
    TIM4->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1; /* Set CH3 PWM mode */
    TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; /* Set CH4 PWM mode */
    TIM4->CCER |= TIM_CCER_CC1E;        /* Enable signal output CH1 */
    TIM4->CCER |= TIM_CCER_CC2E;        /* Enable signal output CH2 */
    TIM4->CCER |= TIM_CCER_CC3E;        /* Enable signal output CH3 */
    TIM4->CCER |= TIM_CCER_CC4E;        /* Enable signal output CH4 */
    TIM4->CR1 |= TIM_CR1_CEN;           /* Enable timer */
}
