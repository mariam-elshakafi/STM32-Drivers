#ifndef UART_H
#define UART_H

/**
 * @brief UART initialization structure
 * This should be configured using proper macros before calling UART_init API
 *
 */
typedef struct
{
u32 module;
u32 baudRate;
u32 stopBits;
u32 parity;
u32 flowControl;
} UART_initStruct;

typedef void (*UART_TxCbF)(void);
typedef void (*UART_RxCbF)(void);

/******** Masks used for GPIO_initStruct parameters *******/

/**
 * @brief UART configuration for module parameter
 * 
 */
#define UART1_MODULE                     0
#define UART2_MODULE                     1
#define UART3_MODULE                     2

/**
 * @brief UART configuration for stopBits parameter
 * 
 */
#define UART_ONE_STOP_BIT                0x00000000
#define UART_TWO_STOP_BIT                0x00002000


/**
 * @brief UART configuration for parity parameter
 * 
 */
#define UART_ODD_PARITY                  0x00001600
#define UART_EVEN_PARITY                 0x00001400
#define UART_NO_PARITY                   0x00000000


/**
 * @brief UART configuration for flowControl parameter
 * 
 */
#define UART_FLOW_CONTROL_ENABLE         0x00000300
#define UART_FLOW_CONTROL_DISABLE        0x00000000


/**
 * @brief Initializes UART object for use
 * Note that you should enable clock for the peripheral before attempting to initialize
 *
 * @param uartObj a UART_initStruct that states the proper configuration for the module
 *
 */
void UART_init(UART_initStruct* uartObj);

/**
 * @brief Sends a data byte through UART
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param data    holds a data byte to be sent
 *
 */
void UART_send(UART_initStruct* uartObj, u8 data);

/**
 * @brief Receives a data byte through UART
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param data    a pointer to where the data received should be saved
 *
 */
void UART_receive(UART_initStruct* uartObj, u8* data);

/**
 * @brief Determines the function to be called when send operation is complete
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param cbf a pointer to the callback function
 *
 */
void UART_setTxCallbackFcn(UART_initStruct* uartObj, UART_TxCbF cbf);

/**
 * @brief Determines the function to be called when receive operation is complete
 *
 * @param uartObj a UART_initStruct that has already been initialized using UART_init()
 * @param cbf a pointer to the callback function
 *
 */
void UART_setRxCallbackFcn(UART_initStruct* uartObj, UART_RxCbF cbf);

#endif