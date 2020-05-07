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
#include "Std_Types.h"
#include "RCC.h"

typedef struct
{
  u32 RCC_CR;
  u32 RCC_CFGR;
  u32 RCC_CIR;
  u32 RCC_APB2RSTR;
  u32 RCC_APB1RSTR;
  u32 RCC_AHBENR;
  u32 RCC_APB2ENR;
  u32 RCC_APB1ENR;
  u32 RCC_BDCR;
  u32 RCC_CSR;
} RCC_regMap;

#define RCC_BASE_ADDRESS    0x40021000
#define RCC_peripheral    ((volatile RCC_regMap *) RCC_BASE_ADDRESS)


/* Mask used by RCC_selectSystemClock() function */
#define RCC_CFGR_SW 0x00000003


/* Masks used by RCC_setClockState() function */
#define RCC_HSI_RDY 0x00000002
#define RCC_HSE_RDY 0x00020000
#define RCC_PLL_RDY 0x02000000


/* Masks used by RCC_configurePLL() function */
#define RCC_PLL_CONFIG 0x003F0000


/* Masks used by RCC_configureMCO() function */
#define RCC_MCO_CONFIG 0x07000000

/* 
* Function Name: RCC_controlAHBPeripheral
* Function Arguments: 
* u32 peripheralNum - takes one of these values
*  RCC_DMA1 
*  RCC_DMA2 
*  RCC_SRAM 
*  RCC_FLITF
*  RCC_CRC  
*  RCC_FSMC 
*  RCC_SDIO 

* u32 status - takes one of these values
*  ENABLE
*  DISABLE
*/
void RCC_controlAHBPeripheral(u32 peripheralNum, u32 status)
{
  switch(status)
  {
    case DISABLE:
      (RCC_peripheral->RCC_AHBENR) &= ~peripheralNum;
    break;
    
    case ENABLE:
      (RCC_peripheral->RCC_AHBENR) |= peripheralNum;
    break;
  }
}


/**
* Function Name: RCC_controlAPB2Peripheral
* Usage: Disable/Enable peripherals on APB2
* Function Arguments: 
* u32 peripheralNum - takes one of these values
* RCC_AFIO  
* RCC_GPIOA 
* RCC_GPIOB 
* RCC_GPIOC 
* RCC_GPIOD 
* RCC_GPIOE 
* RCC_GPIOF 
* RCC_GPIOG 
* RCC_ADC1  
* RCC_ADC2  
* RCC_TIM1  
* RCC_SPI1  
* RCC_TIM8  
* RCC_USART1
* RCC_ADC3  
* RCC_TIM9  
* RCC_TIM10 
* RCC_TIM11 

* u32 status - takes one of these values
*  ENABLE
*  DISABLE
*/
void RCC_controlAPB2Peripheral(u32 peripheralNum, u32 status)
{
  switch(status)
  {
    case DISABLE:
      (RCC_peripheral->RCC_APB2ENR) &= ~peripheralNum;
    break;
    
    case ENABLE:
      (RCC_peripheral->RCC_APB2ENR) |= peripheralNum;
    break;
  }
}


/**
* Function Name: RCC_controlAPB1Peripheral
* Usage: Disable/Enable peripherals on APB1
* Function Arguments: 
* u32 peripheralNum - takes one of these values
* RCC_TIM2    
* RCC_TIM3    
* RCC_TIM4    
* RCC_TIM5    
* RCC_TIM6    
* RCC_TIM7    
* RCC_TIM12   
* RCC_TIM13   
* RCC_TIM14   
* RCC_WWDG    
* RCC_SPI2_I2S
* RCC_SPI3_I2S
* RCC_USART2  
* RCC_USART3  
* RCC_UART4   
* RCC_UART5   
* RCC_I2C1    
* RCC_I2C2    
* RCC_USB     
* RCC_CAN     
* RCC_BKP     
* RCC_PWR     
* RCC_DAC     

* u32 status - takes one of these values
*  ENABLE
*  DISABLE
*/

void RCC_controlAPB1Peripheral(u32 peripheralNum, u32 status)
{
  switch(status)
  {
    case DISABLE:
      (RCC_peripheral->RCC_APB1ENR) &= ~peripheralNum;
    break;
    
    case ENABLE:
      (RCC_peripheral->RCC_APB1ENR) |= peripheralNum;
    break;
  }
}


/**
* Function Name: RCC_selectSystemClock
* Usage: Select clock source for the system
* Function Arguments:
* u32 sysClkNum - takes one of these values
* RCC_sysClk_HSI
* RCC_sysClk_HSE
* RCC_sysClk_PLL
*/
void RCC_selectSystemClock(u32 sysClkNum)
{
  u32 RCC_CFGR_TEMP = RCC_peripheral->RCC_CFGR;
  RCC_CFGR_TEMP &= ~RCC_CFGR_SW;
  RCC_CFGR_TEMP |= sysClkNum;
  (RCC_peripheral->RCC_CFGR) = RCC_CFGR_TEMP;
}


/**
* Function Name: RCC_selectSystemClock
* Usage: RCC_ON/RCC_OFF a clock source
* Function Arguments:
* u32 clkNum - takes one of these values
* RCC_HSI_ON
* RCC_HSE_ON
* RCC_PLL_ON

* u32 status - takes one of these values
* RCC_ON
* RCC_OFF
*/
void RCC_setClockState(u32 clkNum, u32 status)
{
  switch(status)
  {
    case RCC_OFF:
      (RCC_peripheral->RCC_CR) &= ~clkNum;
    break;
    
    case RCC_ON:
      (RCC_peripheral->RCC_CR) |= clkNum;
      while(clkNum == RCC_HSI_ON && !((RCC_peripheral->RCC_CR) & RCC_HSI_RDY));
      while(clkNum == RCC_HSE_ON && !((RCC_peripheral->RCC_CR) & RCC_HSE_RDY));
      while(clkNum == RCC_PLL_ON && !((RCC_peripheral->RCC_CR) & RCC_PLL_RDY));
    break;
  }
}


/**
* Function Name: RCC_configurePLL
* Usage: configure PLL source & speed
* Function Arguments:
* u32 pllSrc - takes one of these values
* RCC_PLLSRC_HSI      
* RCC_PLLSRC_HSE      
* RCC_PLLSRC_HSE_DIV_2

* u32 speedMul - takes one of these values
* RCC_PLLMUL_SPEED_2 
* RCC_PLLMUL_SPEED_3 
* RCC_PLLMUL_SPEED_4 
* RCC_PLLMUL_SPEED_5 
* RCC_PLLMUL_SPEED_6 
* RCC_PLLMUL_SPEED_7 
* RCC_PLLMUL_SPEED_8 
* RCC_PLLMUL_SPEED_9 
* RCC_PLLMUL_SPEED_10
* RCC_PLLMUL_SPEED_11
* RCC_PLLMUL_SPEED_12
* RCC_PLLMUL_SPEED_13
* RCC_PLLMUL_SPEED_14
* RCC_PLLMUL_SPEED_15
* RCC_PLLMUL_SPEED_16
*/
void RCC_configurePLL(u32 pllSrc, u32 speedMul)
{
  (RCC_peripheral->RCC_CFGR) &= ~RCC_PLL_CONFIG;
  (RCC_peripheral->RCC_CFGR) |= pllSrc;
  (RCC_peripheral->RCC_CFGR) |= speedMul;
}



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
*/
void RCC_configurePrescalers(u32 target, u32 preValue)
{
  u32 RCC_CFGR_TEMP = RCC_peripheral->RCC_CFGR;
  RCC_CFGR_TEMP &= ~target;
  RCC_CFGR_TEMP |= preValue;
  (RCC_peripheral->RCC_CFGR) = RCC_CFGR_TEMP;
}


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
void RCC_configureMCO(u32 clkNum)
{
  (RCC_peripheral->RCC_CFGR) &= ~RCC_MCO_CONFIG;
  (RCC_peripheral->RCC_CFGR) |= clkNum;
}
