/* STD lib */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* CMSIS */
#include "stm32f103xb.h"

/* User */
#include "RCC.h"


/******************************************************************************/
/* Definitions ****************************************************************/
/******************************************************************************/
#define CAN_IRQ_PRIORITY            5u
#define CAN_MESSAGE_DATA_LENGTH     8u


/******************************************************************************/
/* Type definitions ***********************************************************/
/******************************************************************************/
typedef struct {
    uint32_t RIR;
    uint32_t RDTR;
    uint32_t RDLR;
    uint32_t RDHR;
} CAN_RX_message_t;


typedef struct {
    uint32_t TIR;
    uint32_t TDTR;
    uint32_t TDLR;
    uint32_t TDHR;
} CAN_TX_message_t;


/******************************************************************************/
/* Static function prototypes *************************************************/
/******************************************************************************/
static void CAN_Init();
static void CAN_FilterInit(void);
static bool CAN_Transmit(const CAN_TX_message_t *const TxMessage);
static bool CAN_Receive(CAN_RX_message_t *const RxMessage);


/******************************************************************************/
/* Interrupts *****************************************************************/
/******************************************************************************/
/**
 * CAN receive IRQ handler.
 * Receive messages from CAN.
 */
void USB_LP_CAN1_RX0_IRQHandler(void) {
    CAN_RX_message_t CAN_RX_message;

    /* Receive CAN message from all CAN RX mailboxes */
    while (CAN_Receive(&CAN_RX_message)) {
        /* Do something here */

    }
}




/******************************************************************************/
/* Main ***********************************************************************/
/******************************************************************************/
int main(void) {
    CAN_TX_message_t CAN_TX_message;    /* CAN message to send */
    uint8_t data = 0u;                  /* Value to send */

    SystemClock_Init();
    CAN_Init();

    while (1) {
        memset(&CAN_TX_message, 0u, sizeof(CAN_TX_message_t));
        /* Fill CAN message data length */
        CAN_TX_message.TDTR |= CAN_MESSAGE_DATA_LENGTH;
        /* Fill CAN low data */
        CAN_TX_message.TDLR |= data;
        CAN_TX_message.TDLR |= (data + 1u) << 8u;
        CAN_TX_message.TDLR |= (data + 2u) << 16u;
        CAN_TX_message.TDLR |= (data + 3u) << 24u;
        /* Fill CAN high data */
        CAN_TX_message.TDHR |= (data + 4u);
        CAN_TX_message.TDHR |= (data + 5u) << 8u;
        CAN_TX_message.TDHR |= (data + 6u) << 16u;
        CAN_TX_message.TDHR |= (data + 7u) << 24u;
        /* Change value to send */
        ++data;

        CAN_Transmit(&CAN_TX_message);
        StupidDelay_ms(10u);
    }
}




/******************************************************************************/
/* Private functions **********************************************************/
/******************************************************************************/
static void CAN_Init() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; /* Enable GPIOA clock*/

    /* CAN Tx pin init */
    GPIOA->CRH &= ~GPIO_CRH_CNF12;      /* Clear bits */
    GPIOA->CRH |= GPIO_CRH_CNF12_1;     /* AF output push-pull */
    GPIOA->CRH |= GPIO_CRH_MODE12;      /* Output mode 50 Mhz */

    /* CAN Rx pin init */
    GPIOA->CRH &= ~GPIO_CRH_CNF11;      /* Clear bits */
    GPIOA->CRH |= GPIO_CRH_CNF11_0;     /* Floating input */
    GPIOA->CRH &= ~GPIO_CRH_MODE11;     /* Input mode */

    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN; /* Enable CAN clock */
    CAN1->MCR &= ~CAN_MCR_SLEEP;        /* Exit from sleep mode */

    /* Request initialisation and wait it */
    CAN1->MCR |= CAN_MCR_INRQ ;
    while((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) {
        ;
    }

    CAN1->MCR |= CAN_MCR_ABOM;          /* Turn on bus-off management */
    CAN1->BTR = 0x001e0001u;            /* Baud rate 1 Mbit/s */
    CAN1->IER |= CAN_IER_FMPIE0;        /* Enable FIFO0 message pending IRQ */


    /*------------------------------------------------------------------------*/
    /* Debug loopback mode ---------------------------------------------------*/
    /*------------------------------------------------------------------------*/
    CAN1->BTR |= CAN_BTR_LBKM;          /* Enable loop back mode */
    CAN1->BTR |= CAN_BTR_SILM;          /* Enbale silent mode */


    NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, CAN_IRQ_PRIORITY); /* Set interrupt
                                                               * priority */
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);   /* Enable interrupt */

    /* Leave initialisation and wait it */
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while((CAN1->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) {
        ;
    }

    /* Init CAN filters */
    CAN_FilterInit();
}


/**
 * Init CAN filters for receiving all messages from bus
 */
static void CAN_FilterInit(void) {
    CAN1->FMR |= CAN_FMR_FINIT;     /* Initialization mode for the filter */

    /* Filter 0 */
    CAN1->FS1R |= CAN_FS1R_FSC0;
    CAN1->sFilterRegister[0u].FR1 = 0x0000u;
    CAN1->sFilterRegister[0u].FR2 = 0x0000u;
    CAN1->FA1R |= CAN_FA1R_FACT0;

    CAN1->FMR &= ~CAN_FMR_FINIT;    /* Leave the initialization mode  */
}


/**
 * Try to put CAN message to mailbox.
 * @param  CAN_TX_message Pointer to CAN message
 * @return                True if message put in mailbox
 */
static bool CAN_Transmit(const CAN_TX_message_t *const TxMessage) {
    bool message_transmitted = false;
    uint8_t first_empty_mailbox = 0xFFu;

    /* Define first empty mailbox */
    if ((CAN1->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
        first_empty_mailbox = 0u;
    } else if ((CAN1->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
        first_empty_mailbox = 1u;
    } else if ((CAN1->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
        first_empty_mailbox = 2u;
    } else {
    }

    if (first_empty_mailbox != 0xFFu) {
        message_transmitted = true;
        CAN1->sTxMailBox[first_empty_mailbox].TIR = TxMessage->TIR;
        CAN1->sTxMailBox[first_empty_mailbox].TDTR = TxMessage->TDTR;
        CAN1->sTxMailBox[first_empty_mailbox].TDLR = TxMessage->TDLR;
        CAN1->sTxMailBox[first_empty_mailbox].TDHR = TxMessage->TDHR;
        CAN1->sTxMailBox[first_empty_mailbox].TIR |= CAN_TI0R_TXRQ;
    }

    return message_transmitted;
}


/**
 * Receive CAN message from mailbox.
 * @param  RxMessage Pointer to CAN message
 * @return           True if message received
 */
static bool CAN_Receive(CAN_RX_message_t *const RxMessage) {
    bool message_received = false;
    int8_t mailbox_num;

    if ((CAN1->RF0R & CAN_RF0R_FMP0) != 0u) {
        message_received = true;
        mailbox_num = (CAN1->RF0R & CAN_RF0R_FMP0) - 1u;
        RxMessage->RIR = CAN1->sFIFOMailBox[mailbox_num].RIR;
        RxMessage->RDTR = CAN1->sFIFOMailBox[mailbox_num].RDTR;
        RxMessage->RDLR = CAN1->sFIFOMailBox[mailbox_num].RDLR;
        RxMessage->RDHR = CAN1->sFIFOMailBox[mailbox_num].RDHR;

        /* Clear mailbox flag */
        CAN1->RF0R |= CAN_RF0R_RFOM0;
    }
    return message_received;
}
