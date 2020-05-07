/**
 * @file NVIC.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the user interface for the NVIC driver
 * @version 0.1
 * @date 2020-03-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef NVIC_H_
#define NVIC_H_
/** interruptNum **/
#define NVIC_IRQNUM_WWDG            0
#define NVIC_IRQNUM_PVD             1
#define NVIC_IRQNUM_TAMPER          2
#define NVIC_IRQNUM_RTC             3
#define NVIC_IRQNUM_FLASH           4
#define NVIC_IRQNUM_RCC             5
#define NVIC_IRQNUM_EXTI0           6
#define NVIC_IRQNUM_EXTI1           7
#define NVIC_IRQNUM_EXTI2           8
#define NVIC_IRQNUM_EXTI3           9
#define NVIC_IRQNUM_EXTI4           10
#define NVIC_IRQNUM_DMA1_CHANNEL1   11
#define NVIC_IRQNUM_DMA1_CHANNEL2   12
#define NVIC_IRQNUM_DMA1_CHANNEL3   13
#define NVIC_IRQNUM_DMA1_CHANNEL4   14
#define NVIC_IRQNUM_DMA1_CHANNEL5   15
#define NVIC_IRQNUM_DMA1_CHANNEL6   16
#define NVIC_IRQNUM_DMA1_CHANNEL7   17
#define NVIC_IRQNUM_ADC1_2          18
#define NVIC_IRQNUM_USB_HP_CAN_TX   19
#define NVIC_IRQNUM_USB_HP_CAN_RX0  20
#define NVIC_IRQNUM_CAN_RX1         21
#define NVIC_IRQNUM_CAN_SCE         22
#define NVIC_IRQNUM_EXTI9_5         23
#define NVIC_IRQNUM_TIM1_BRK        24
#define NVIC_IRQNUM_TIM1_UP         25
#define NVIC_IRQNUM_TIM1_TRG_COM    26
#define NVIC_IRQNUM_TIM1_CC         27
#define NVIC_IRQNUM_TIM2            28
#define NVIC_IRQNUM_TIM3            29
#define NVIC_IRQNUM_TIM4            30
#define NVIC_IRQNUM_I2C1_EV         31

#define NVIC_IRQNUM_I2C1_ER         32
#define NVIC_IRQNUM_I2C2_EV         33
#define NVIC_IRQNUM_I2C2_ER         34
#define NVIC_IRQNUM_SPI1            35
#define NVIC_IRQNUM_SPI2            36
#define NVIC_IRQNUM_USART1          37
#define NVIC_IRQNUM_USART2          38
#define NVIC_IRQNUM_USART3          39
#define NVIC_IRQNUM_EXTI15_10       40
#define NVIC_IRQNUM_RTC_ALARM       41
#define NVIC_IRQNUM_USB_WAKE_UP     42
#define NVIC_IRQNUM_TIM8_BRK        43
#define NVIC_IRQNUM_TIM8_UP         44
#define NVIC_IRQNUM_TIM8_TRG_COM    45
#define NVIC_IRQNUM_TIM8_CC         46
#define NVIC_IRQNUM_ADC3            47
#define NVIC_IRQNUM_FSMC            48
#define NVIC_IRQNUM_SDIO            49
#define NVIC_IRQNUM_TIM5            50
#define NVIC_IRQNUM_SPI3            51
#define NVIC_IRQNUM_UART4           52
#define NVIC_IRQNUM_UART5           53
#define NVIC_IRQNUM_TIM6            54
#define NVIC_IRQNUM_TIM7            55
#define NVIC_IRQNUM_DMA2_Channel1   56
#define NVIC_IRQNUM_DMA2_Channel2   57
#define NVIC_IRQNUM_DMA2_Channel3   58
#define NVIC_IRQNUM_DMA2_Channel4_5 59

/********* Masks used by void NVIC_controlInterrupt(u8 interruptNum, u8 status) *********/
/** status **/
#define NVIC_DISABLE 0
#define NVIC_ENABLE  1

/********* Masks used by void NVIC_controlPendingFlag(u8 interruptNum, u8 val) *********/
/** val **/
#define NVIC_RESET 0
#define NVIC_SET   1

/**
 * @brief Sets and resets the interrupts
 * 
 * @param interruptNum The Interrupt number
 * @param status The state 
 *                  NVIC_DISABLE
 *                  NVIC_ENABLE 
 */
extern void NVIC_controlInterrupt(u8 interruptNum, u8 status);
/**
 * @brief Sets and resets The pending flag
 * 
 * @param interruptNum The Interrupt number
 * @param val the value to be set
 *                      NVIC_RESET
 *                      NVIC_SET  
 */
extern void NVIC_controlPendingFlag(u8 interruptNum, u8 val);
/**
 * @brief Gets the active flag state
 * 
 * @param interruptNum the number of the interrupt
 * @return u8 
 */
extern u8 NVIC_getActiveFlagStatus(u8 interruptNum);
/**
 * @brief Configures the periority of the interrupt
 * 
 * @param interruptNum the number of the interrupt
 * @param priority The periority
 */
extern void NVIC_configurePriority(u8 interruptNum, u8 priority);
/**
 * @brief Gets the priority of the interrupt 
 * 
 * @param interruptNum the number of the interrupt
 * @return u8 
 */
extern u8 NVIC_getPriority(u8 interruptNum);
/**
 * @brief Controls All of the prephirals
 * 
 * @param status
 *          NVIC_ENABLE
 *          NVIC_DISABLE 
 */
extern void NVIC_controlAllPeripheral(u8 status);
/**
 * @brief Controls The Fault flag
 * 
 * @param status
 *          NVIC_ENABLE
 *          NVIC_DISABLE
 */
extern void NVIC_controlFault(u8 status);
/**
 * @brief Filters the interrupt
 * 
 * @param priority the priority of the interrupt
 */
extern void NVIC_filterInterrupts(u8 priority);
#endif