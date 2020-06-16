#include "STD_TYPES.h"
#include "UART.h"
#include "UART_CFG.h"

typedef struct
{
u32 SR;
u32 DR;
u32 BRR;
u32 CR1;
u32 CR2;
u32 CR3;
u32 GTPR;
} UART_regMap;


#define UART_NUM_MODULE                       3

/**
 * @brief UART base addresses
 * 
 */
#define UART1_BASE_ADDRESS                    0x40013800
#define UART2_BASE_ADDRESS                    0x40004400
#define UART3_BASE_ADDRESS                    0x40004800


/** CR1 Masks **/
#define UART_CR1_PARITY_CLR                   0xFFFFE9FF
#define UART_CR1_UE_SET                       0x00002000
#define UART_CR1_PEIE_SET                     0x00000100
#define UART_CR1_TXEIE_SET                    0x00000080
#define UART_CR1_TXEIE_CLR                    0xFFFFFF7F
#define UART_CR1_TCIE_SET                     0x00000040
#define UART_CR1_RXNEIE_SET                   0x00000020
#define UART_CR1_IDLEIE_SET                   0x00000010
#define UART_CR1_TE_SET                       0x00000008
#define UART_CR1_RE_SET                       0x00000004


/** CR2 Masks **/
#define UART_CR2_STOP_CLR                     0xFFFFCFFF


/** CR3 Masks **/
#define UART_CR3_FLOWCONTROL_CLR              0xFFFFFCFF

/** SR Masks **/
#define UART_SR_TXE_SET                       0x00000080
#define UART_SR_TC_SET                        0x00000040
#define UART_SR_RXNE_SET                      0x00000020


static UART_TxCbF TxCbF[UART_NUM_MODULE] = {NULL, NULL, NULL};
static UART_RxCbF RxCbF[UART_NUM_MODULE] = {NULL, NULL, NULL};
static u32 UART_baseAddress[UART_NUM_MODULE] = {UART1_BASE_ADDRESS, UART2_BASE_ADDRESS, UART3_BASE_ADDRESS};
static u8* receivedData[UART_NUM_MODULE] = {NULL, NULL, NULL};


/**
 * @brief Initializes UART object for use
 * Note that you should enable clock for the peripheral before attempting to initialize
 *
 * @param uartObj a UART_initStruct that states the proper configuration for the module
 *
 */
void UART_IRQGeneralHandler(u32 uartmodule)
{
    volatile UART_regMap* uartBase = (volatile UART_regMap*)UART_baseAddress[uartmodule];

    if (uartBase->SR & UART_SR_TXE_SET)
    {

        uartBase->CR1 &= UART_CR1_TXEIE_CLR;
        if(TxCbF[uartmodule])
        {
            TxCbF[uartmodule]();
        }

    }

    if (uartBase->SR & UART_SR_RXNE_SET)
    {
        *receivedData[uartmodule] = uartBase->DR;
        if(RxCbF[uartmodule])
        {
            RxCbF[uartmodule]();
        }
    }
}

void USART1_IRQHandler(void)
{
	UART_IRQGeneralHandler(UART1_MODULE);
}


void USART2_IRQHandler(void)
{
	UART_IRQGeneralHandler(UART2_MODULE);
}


void USART3_IRQHandler(void)
{
	UART_IRQGeneralHandler(UART3_MODULE);
}

/**
 * @brief Initializes UART object for use
 * Note that you should enable clock for the peripheral before attempting to initialize
 *
 * @param uartObj a UART_initStruct that states the proper configuration for the module
 *
 */
void UART_init(UART_initStruct* uartObj)
{
    volatile UART_regMap* uartBase = (volatile UART_regMap*)UART_baseAddress[uartObj->module];

    uartBase->BRR = (u16)((UART_CLOCK)/((uartObj->baudRate)));

    uartBase->CR2 &= UART_CR2_STOP_CLR;
    uartBase->CR2 |= uartObj->stopBits;
    
    uartBase->CR1 &= UART_CR1_PARITY_CLR;
    uartBase->CR1 |= uartObj->parity;
    
    uartBase->CR3 &= UART_CR3_FLOWCONTROL_CLR;
    uartBase->CR3 |= uartObj->flowControl;
    
    uartBase->CR1 |= ( UART_CR1_UE_SET | UART_CR1_TE_SET | UART_CR1_RE_SET | UART_CR1_RXNEIE_SET );
}

/**
 * @brief Sends a data byte through UART
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param data    holds a data byte to be sent
 *
 */
void UART_send(UART_initStruct* uartObj, u8 data)
{
    volatile UART_regMap* uartBase = (volatile UART_regMap*)UART_baseAddress[uartObj->module];
    uartBase->DR = data;
    uartBase->CR1 |= UART_CR1_TXEIE_SET;
}

/**
 * @brief Receives a data byte through UART
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param data    a pointer to where the data received should be saved
 *
 */
void UART_receive(UART_initStruct* uartObj, u8* data)
{
    receivedData[uartObj->module] = data;
}

/**
 * @brief Determines the function to be called when send operation is complete
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param cbf a pointer to the callback function
 *
 */
void UART_setTxCallbackFcn(UART_initStruct* uartObj, UART_TxCbF cbf)
{
    TxCbF[uartObj->module] = cbf;
}

/**
 * @brief Determines the function to be called when receive operation is complete
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param cbf a pointer to the callback function
 *
 */
void UART_setRxCallbackFcn(UART_initStruct* uartObj, UART_RxCbF cbf)
{
    RxCbF[uartObj->module] = cbf;
}
