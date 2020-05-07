/**
 * @file RCC.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the user interface for the RCC Driver
 * @version 0.1
 * @date 2020-03-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef RCC_H
#define RCC_H

/* Macros used in RCC_controlXPeripheral() input */
#define ENABLE              1
#define DISABLE             0

/* Macros used in RCC_controlAHBPeripheral() input */
#define RCC_DMA1                0x00000001
#define RCC_DMA2                0x00000002
#define RCC_SRAM                0x00000004
#define RCC_FLITF               0x00000010
#define RCC_CRC                 0x00000040
#define RCC_FSMC                0x00000100
#define RCC_SDIO                0x00000400

/* Macros used in RCC_controlAPB2Peripheral() input */
#define RCC_AFIO                0x00000001
#define RCC_GPIOA               0x00000004
#define RCC_GPIOB               0x00000008
#define RCC_GPIOC               0x00000010
#define RCC_GPIOD               0x00000020
#define RCC_GPIOE               0x00000040
#define RCC_GPIOF               0x00000080
#define RCC_GPIOG               0x00000100
#define RCC_ADC1                0x00000200
#define RCC_ADC2                0x00000400
#define RCC_TIM1                0x00000800
#define RCC_SPI1                0x00001000
#define RCC_TIM8                0x00002000
#define RCC_USART1              0x00004000
#define RCC_ADC3                0x00008000
#define RCC_TIM9                0x00080000
#define RCC_TIM10               0x00100000
#define RCC_TIM11               0x00200000


/* Macros used in RCC_controlAPB1Peripheral() input */
#define RCC_TIM2                0x00000001
#define RCC_TIM3                0x00000002
#define RCC_TIM4                0x00000004
#define RCC_TIM5                0x00000008
#define RCC_TIM6                0x00000010
#define RCC_TIM7                0x00000020
#define RCC_TIM12               0x00000040
#define RCC_TIM13               0x00000080
#define RCC_TIM14               0x00000100
#define RCC_WWDG                0x00000800
#define RCC_SPI2_I2S            0x00004000
#define RCC_SPI3_I2S            0x00008000
#define RCC_USART2              0x00020000
#define RCC_USART3              0x00040000
#define RCC_UART4               0x00080000
#define RCC_UART5               0x00100000
#define RCC_I2C1                0x00200000
#define RCC_I2C2                0x00400000
#define RCC_USB                 0x00800000
#define RCC_CAN                 0x02000000
#define RCC_BKP                 0x08000000
#define RCC_PWR                 0x10000000
#define RCC_DAC                 0x20000000


/* Macros used for RCC_selectSystemClock() function input */
#define RCC_sysClk_HSI 0x00000000
#define RCC_sysClk_HSE 0x00000001
#define RCC_sysClk_PLL 0x00000002

/* Macros used for RCC_setClockState() function input */
#define RCC_OFF 0
#define RCC_ON  1

#define RCC_HSI_ON 0x00000001
#define RCC_HSE_ON 0x00010000
#define RCC_PLL_ON 0x01000000

/* Macros used by RCC_configurePLL() function */
#define RCC_PLLSRC_HSI       0x00000000
#define RCC_PLLSRC_HSE       0x00010000
#define RCC_PLLSRC_HSE_DIV_2 0x00030000


#define RCC_PLLMUL_SPEED_2  0x00000000
#define RCC_PLLMUL_SPEED_3  0x00040000
#define RCC_PLLMUL_SPEED_4  0x00080000
#define RCC_PLLMUL_SPEED_5  0x000C0000
#define RCC_PLLMUL_SPEED_6  0x00100000
#define RCC_PLLMUL_SPEED_7  0x00140000
#define RCC_PLLMUL_SPEED_8  0x00180000
#define RCC_PLLMUL_SPEED_9  0x001C0000
#define RCC_PLLMUL_SPEED_10 0x00200000
#define RCC_PLLMUL_SPEED_11 0x00240000
#define RCC_PLLMUL_SPEED_12 0x00280000
#define RCC_PLLMUL_SPEED_13 0x002C0000
#define RCC_PLLMUL_SPEED_14 0x00300000
#define RCC_PLLMUL_SPEED_15 0x00340000
#define RCC_PLLMUL_SPEED_16 0x00380000


/* Macros used by RCC_configurePrescalers() function */
#define RCC_USB_PRESCALER  0x00400000
#define RCC_ADC_PRESCALER  0x0000C000
#define RCC_APB2_PRESCALER 0x00003800
#define RCC_APB1_PRESCALER 0x00000700
#define RCC_AHB_PRESCALER  0x000000F0

#define RCC_USB_DIVIDED    0x00000000
#define RCC_USB_NDIVIDED   0x00400000

#define RCC_ADC_DIV_2      0x00000000
#define RCC_ADC_DIV_4      0x00004000
#define RCC_ADC_DIV_6      0x00008000
#define RCC_ADC_DIV_8      0x0000C000

#define RCC_APB2_NDIVIDED  0x00000000
#define RCC_APB2_DIV_2     0x00002000
#define RCC_APB2_DIV_4     0x00002800
#define RCC_APB2_DIV_8     0x00003000
#define RCC_APB2_DIV_16    0x00003800

#define RCC_APB1_NDIVIDED  0x00000000
#define RCC_APB1_DIV_2     0x00000400
#define RCC_APB1_DIV_4     0x00000500
#define RCC_APB1_DIV_8     0x00000600
#define RCC_APB1_DIV_16    0x00000700

#define RCC_AHB_NDIVIDED  0x00000000
#define RCC_AHB_DIV_2     0x00000080
#define RCC_AHB_DIV_4     0x00000090
#define RCC_AHB_DIV_8     0x000000A0
#define RCC_AHB_DIV_16    0x000000B0
#define RCC_AHB_DIV_64    0x000000C0
#define RCC_AHB_DIV_128   0x000000D0
#define RCC_AHB_DIV_256   0x000000E0
#define RCC_AHB_DIV_512   0x000000F0

#define RCC_MCO_NOSRC  0x00000000
#define RCC_MCO_SYSCLK 0x04000000
#define RCC_MCO_HSI    0x05000000
#define RCC_MCO_HSE    0x06000000
#define RCC_MCO_PLL    0x07000000

/**
* Function Name: RCC_controlAHBPeripheral
* Usage: Disable/Enable peripherals on AHB
* Function Arguments: 
* u32 peripheralNum - takes one of these values
*   RCC_DMA1 
*   RCC_DMA2 
*   RCC_SRAM 
*   RCC_FLITF
*   RCC_CRC  
*   RCC_FSMC 
*   RCC_SDIO 

* u32 status - takes one of these values
*   ENABLE
*   DISABLE
*/
void RCC_controlAHBPeripheral(u32 peripheralNum, u32 status);

/**
* Function Name: RCC_controlAPB2Peripheral
* Usage: Disable/Enable peripherals on APB2
* Function Arguments: 
* u32 peripheralNum - takes one of these values
*   RCC_AFIO  
*   RCC_GPIOA 
*   RCC_GPIOB 
*   RCC_GPIOC 
*   RCC_GPIOD 
*   RCC_GPIOE 
*   RCC_GPIOF 
*   RCC_GPIOG 
*   RCC_ADC1  
*   RCC_ADC2  
*   RCC_TIM1  
*   RCC_SPI1  
*   RCC_TIM8  
*   RCC_USART1
*   RCC_ADC3  
*   RCC_TIM9  
*   RCC_TIM10 
*   RCC_TIM11 

* u32 status - takes one of these values
*   ENABLE
*   DISABLE
*/
void RCC_controlAPB2Peripheral(u32 peripheralNum, u32 status);


/**
* Function Name: RCC_controlAPB1Peripheral
* Usage: Disable/Enable peripherals on APB1
* Function Arguments: 
* u32 peripheralNum - takes one of these values
*   RCC_TIM2    
*   RCC_TIM3    
*   RCC_TIM4    
*   RCC_TIM5    
*   RCC_TIM6    
*   RCC_TIM7    
*   RCC_TIM12   
*   RCC_TIM13   
*   RCC_TIM14   
*   RCC_WWDG    
*   RCC_SPI2_I2S
*   RCC_SPI3_I2S
*   RCC_USART2  
*   RCC_USART3  
*   RCC_UART4   
*   RCC_UART5   
*   RCC_I2C1    
*   RCC_I2C2    
*   RCC_USB     
*   RCC_CAN     
*   RCC_BKP     
*   RCC_PWR     
*   RCC_DAC     

* u32 status - takes one of these values
*   ENABLE
*   DISABLE
*/
void RCC_controlAPB1Peripheral(u32 peripheralNum, u32 status);


/**
* Function Name: RCC_selectSystemClock
* Usage: Select clock source for the system
* Function Arguments:
* u32 sysClkNum - takes one of these values
*   RCC_sysClk_HSI
*   RCC_sysClk_HSE
*   RCC_sysClk_PLL
*/
void RCC_selectSystemClock(u32 sysClkNum);

/**
* Function Name: RCC_selectSystemClock
* Usage: RCC_ON/RCC_OFF a clock source
* Function Arguments:
* u32 clkNum - takes one of these values
*   RCC_HSI_ON
*   RCC_HSE_ON
*   RCC_PLL_ON

* u32 status - takes one of these values
*   RCC_ON
*   RCC_OFF
*/
void RCC_setClockState(u32 clkNum, u32 status);


/**
* Function Name: RCC_configurePLL
* Usage: configure PLL source & speed
* Function Arguments:
* u32 pllSrc - takes one of these values
*   RCC_PLLSRC_HSI      
*   RCC_PLLSRC_HSE      
*   RCC_PLLSRC_HSE_DIV_2

* u32 speedMul - takes one of these values
*   RCC_PLLMUL_SPEED_2 
*   RCC_PLLMUL_SPEED_3 
*   RCC_PLLMUL_SPEED_4 
*   RCC_PLLMUL_SPEED_5 
*   RCC_PLLMUL_SPEED_6 
*   RCC_PLLMUL_SPEED_7 
*   RCC_PLLMUL_SPEED_8 
*   RCC_PLLMUL_SPEED_9 
*   RCC_PLLMUL_SPEED_10
*   RCC_PLLMUL_SPEED_11
*   RCC_PLLMUL_SPEED_12
*   RCC_PLLMUL_SPEED_13
*   RCC_PLLMUL_SPEED_14
*   RCC_PLLMUL_SPEED_15
*   RCC_PLLMUL_SPEED_16
*/
void RCC_configurePLL(u32 pllSrc, u32 speedMul);


/**
* Function Name: RCC_configurePrescalers
* Usage: configure prescalers for a specific target
* Function Arguments:
* u32 target - takes one of these values
*   RCC_USB_PRESCALER 
*   RCC_ADC_PRESCALER 
*   RCC_APB2_PRESCALER
*   RCC_APB1_PRESCALER
*   RCC_AHB_PRESCALER 

* u32 preValue - takes one of these values
*   RCC_USB_DIVIDED  
*   RCC_USB_NDIVIDED 
*   RCC_ADC_DIV_2    
*   RCC_ADC_DIV_4    
*   RCC_ADC_DIV_6    
*   RCC_ADC_DIV_6    
*   RCC_APB2_NDIVIDED
*   RCC_APB2_DIV_2   
*   RCC_APB2_DIV_4   
*   RCC_APB2_DIV_8   
*   RCC_APB2_DIV_16  
*   RCC_APB1_NDIVIDED
*   RCC_APB1_DIV_2   
*   RCC_APB1_DIV_4   
*   RCC_APB1_DIV_8   
*   RCC_APB1_DIV_16  
*   RCC_AHB_NDIVIDED
*   RCC_AHB_DIV_2   
*   RCC_AHB_DIV_4   
*   RCC_AHB_DIV_8   
*   RCC_AHB_DIV_16  
*   RCC_AHB_DIV_64  
*   RCC_AHB_DIV_128 
*   RCC_AHB_DIV_256 
*   RCC_AHB_DIV_512 

*/
void RCC_configurePrescalers(u32 target, u32 preValue);


/**
* Function Name: RCC_configureMCO
* Usage: configure MCO source
* Function Arguments:
* u32 clkNum - takes one of these values
*   RCC_MCO_NOSRC 
*   RCC_MCO_SYSCLK
*   RCC_MCO_HSI   
*   RCC_MCO_HSE   
*   RCC_MCO_PLL   
*/
void RCC_configureMCO(u32 clkNum);

#endif
