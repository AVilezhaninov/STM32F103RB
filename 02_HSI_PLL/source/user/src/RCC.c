#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define AHB_PRESCALER           RCC_CFGR_HPRE_DIV1
#define APB1_PRESCALER          RCC_CFGR_PPRE1_DIV2
#define APB2_PRESCALER          RCC_CFGR_PPRE2_DIV1

#define HSI_STARTUP_TIMEOUT     0x5000u


/******************************************************************************/
/* Exported functions *********************************************************/
/******************************************************************************/
void SystemClock_Init(void) {
    uint32_t StartUpCounter = 0u;
    uint32_t HSIStatus = 0u;

    /* Enable HSI */
    RCC->CR |= RCC_CR_HSION;

    /* Wait till HSI is ready and exit if timeout is reached */
    while ((HSIStatus == 0u) && (StartUpCounter < HSI_STARTUP_TIMEOUT)) {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        ++StartUpCounter;
    }

    if (HSIStatus == RCC_CR_HSIRDY) {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

        /* HCLK */
        RCC->CFGR |= (uint32_t)AHB_PRESCALER;

        /* PCLK2 */
        RCC->CFGR |= (uint32_t)APB2_PRESCALER;

        /* PCLK1 */
        RCC->CFGR |= (uint32_t)APB1_PRESCALER;

        /*  PLL configuration: PLLCLK = (HSI / 2) * 16 = 64 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC |
                                            RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLMULL16);

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY) {
            ;
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
            ;
        }

        SystemCoreClockUpdate();
    } else {
        /* If HSI fails to start-up, the application will have wrong clock
        configuration. User can add here some code to deal with this error */
        while (1) {
            ;
        }
    }
}


uint32_t GetHCLKFrequency(void) {
    return SystemCoreClock;
}


uint32_t GetPCLK1Frequency(void) {
    return GetHCLKFrequency() >>
           APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos];
}


uint32_t GetPCLK2Frequency(void) {
    return GetHCLKFrequency() >>
           APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos];
}


/**
 * Blocking delay in us
 * @param delay [us]
 */
void StupidDelay_us(volatile uint32_t delay) {
    delay *= (SystemCoreClock / 1000000u);

    while (delay-- > 0u) {
        ;
    }
}


/**
 * Blocking delay in ms
 * @param delay [ms]
 */
void StupidDelay_ms(volatile uint32_t delay) {
    delay *= (SystemCoreClock / 1000u);

    while (delay-- > 0u) {
        ;
    }
}
