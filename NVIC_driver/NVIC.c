/**
 * @file NVIC.c
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the implementation for the NVIC Driver
 * @version 0.1
 * @date 2020-03-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "NVIC.h"

typedef struct
{
u32 ISER[3];
u32 RESERVED0[29];
u32 ICER[3];
u32 RESERVED1[29];
u32 ISPR[3];
u32 RESERVED2[29];
u32 ICPR[3];
u32 RESERVED3[29];
u32 IABR[3];
u32 RESERVED4[29];
u32 IPR[21];
} NVIC_regMap;

#define NVIC_BASE_ADDRESS 0xE000E100
#define NVIC_peripheral ((volatile NVIC_regMap *) NVIC_BASE_ADDRESS)


/* IPR set mask */
#define NVIC_IPR_SETMASK    0x000000ff

/**
 * @brief Sets and resets the interrupts
 * 
 * @param interruptNum The Interrupt number
 * @param status The state 
 *                  NVIC_DISABLE
 *                  NVIC_ENABLE 
 */
void NVIC_controlInterrupt(u8 interruptNum, u8 status)
{
  u8 regIdx = (interruptNum >> 5);
  switch (status)
  {
    case NVIC_ENABLE:
    	NVIC_peripheral->ISER[regIdx] = (1 << (interruptNum & 0x1F));
    break;

    case NVIC_DISABLE:
    	NVIC_peripheral->ICER[regIdx] = (1 << (interruptNum & 0x1F));
    break;
  }
}

/**
 * @brief Sets and resets The pending flag
 * 
 * @param interruptNum The Interrupt number
 * @param val the value to be set
 *                      NVIC_RESET
 *                      NVIC_SET  
 */
void NVIC_controlPendingFlag(u8 interruptNum, u8 val)
{
  u8 regIdx = (interruptNum >> 5);
  switch (val)
  {
    case NVIC_SET:
    	NVIC_peripheral->ISPR[regIdx] = (1 << (interruptNum & 0x1F));
    break;

    case NVIC_RESET:
    	NVIC_peripheral->ICPR[regIdx] = (1 << (interruptNum & 0x1F));
    break;
  }
}

/**
 * @brief Gets the active flag state
 * 
 * @param interruptNum the number of the interrupt
 * @return u8 
 */
u8 NVIC_getActiveFlagStatus(u8 interruptNum)
{
  u8 regIdx = (interruptNum >> 5);
  u8 intStat = NVIC_peripheral->IABR[regIdx] & (1 << (interruptNum & 0x1F));
  if (intStat)
  {
    return NVIC_SET;
  }
  else
  {
    return NVIC_RESET;
  }
}

/**
 * @brief Configures the periority of the interrupt
 * 
 * @param interruptNum the number of the interrupt
 * @param priority The periority
 */
void NVIC_configurePriority(u8 interruptNum, u8 priority)
{
  u8 regIdx = (interruptNum >> 2);
  u8 absPrior = (priority << 4);
  u8 shiftVal = ((interruptNum & 0x3) << 3);
  NVIC_peripheral->IPR[regIdx] &= ~(NVIC_IPR_SETMASK << shiftVal);
  NVIC_peripheral->IPR[regIdx] |= absPrior << shiftVal;
}

/**
 * @brief Gets the priority of the interrupt 
 * 
 * @param interruptNum the number of the interrupt
 * @return u8 
 */
u8 NVIC_getPriority(u8 interruptNum)
{
  u8 regIdx = (interruptNum >> 2);
  u8 shiftVal = ((interruptNum & 0x3) << 3);
  u8 priority = (NVIC_peripheral->IPR[regIdx] >> shiftVal) & NVIC_IPR_SETMASK;
  return priority;
}

/**
 * @brief Controls All of the prephirals
 * 
 * @param status
 *          NVIC_ENABLE
 *          NVIC_DISABLE 
 */
void NVIC_controlAllPeripheral(u8 status)
{
  switch(status)
  {
    case NVIC_ENABLE:
      asm("CPSIE I");
    break;

    case NVIC_DISABLE:
      asm("CPSID I");
    break;
  }
}
/**
 * @brief Controls The Fault flag
 * 
 * @param status
 *          NVIC_ENABLE
 *          NVIC_DISABLE
 */
void NVIC_controlFault(u8 status)
{
  switch(status)
  {
    case NVIC_ENABLE:
      asm("CPSIE F");
    break;

    case NVIC_DISABLE:
      asm("CPSID F");
    break;
  }
}
/**
 * @brief Filters the interrupt
 * 
 * @param priority the priority of the interrupt
 */
void NVIC_filterInterrupts(u8 priority)
{
  asm("MOV R0, %0"
      : "=r" (priority));
  asm("MSR BASEPRI, R0");
}
