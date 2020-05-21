/**
 * @file FLASH.c
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the implementation for the Flash driver
 * @version 0.1
 * @date 2020-05-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "STD_TYPES.h"
#include "FLASH.h"

typedef struct
{
u32 ACR;
u32 KEYR;
u32 OPTKEYR;
u32 SR;
u32 CR;
u32 AR;
u32 Reserved;
u32 OBR;
u32 WRPR;
} FPEC_regMap;

#define FPEC_BASE_ADDRESS 0x40022000
#define FPEC_peripheral ((volatile FPEC_regMap *) FPEC_BASE_ADDRESS)


/* Flash Keys */
#define FLASH_RDPRT_KEY    0x00A5
#define FLASH_KEY1         0x45670123
#define FLASH_KEY2         0xCDEF89AB

/* CR Masks */
#define FLASH_CR_PG        0x00000001
#define FLASH_CR_PER       0x00000002
#define FLASH_CR_MER       0x00000004
#define FLASH_CR_STRT      0x00000040
#define FLASH_CR_LOCK      0x00000080

/* SR Masks */
#define FLASH_SR_BSY       0x00000001
#define FLASH_SR_PGERR     0x00000004
#define FLASH_SR_WRPRTERR  0x00000010
#define FLASH_SR_EOP       0x00000020

/**
  * @brief  Get flash status
  *
  * @retval flashStat : a value of the following:
                        FLASH_COMPLETE
                        FLASH_PROG_ERR
                        FLASH_WPROTECT_ERR
                        FLASH_BUSY
                        FLASH_LOCKED
  */
static flashStat FLASH_GetStatus(void)
{
    flashStat status = FLASH_COMPLETE;
    if ( (FPEC_peripheral->CR) & (FLASH_CR_LOCK) )
    {
        status = FLASH_LOCKED;
    }
    else if ( (FPEC_peripheral->SR) & (FLASH_SR_BSY) )
    {
        status = FLASH_BUSY;
    }
    else if ( (FPEC_peripheral->SR) & (FLASH_SR_PGERR) )
    {
        status = FLASH_PROG_ERR;
    }
    else if ( (FPEC_peripheral->SR) & (FLASH_SR_WRPRTERR) )
    {
        status = FLASH_WPROTECT_ERR;
    }
    return status;
}


/**
  * @brief  Wait for busy flag
  *
  */
static void FLASH_WaitForOperation(void)
{
    while( (FPEC_peripheral->SR) & (FLASH_SR_BSY) );
}


/**
  * @brief  Perform flash unlock sequence
  *
  */
static void FLASH_unlock(void)
{
    FPEC_peripheral->KEYR = FLASH_KEY1;
    FPEC_peripheral->KEYR = FLASH_KEY2;
}


/**
  * @brief  Perform flash lock
  *
  */
void FLASH_lock(void)
{
    FPEC_peripheral->CR |= FLASH_CR_LOCK;
}


/**
  * @brief  Write half-word to flash
  *
  * @param  address : holds the flash address to be programmed
            val : holds the desired value
  *
  * @retval flashStat : a value of the following:
                        FLASH_COMPLETE
                        FLASH_PROG_ERR
                        FLASH_WPROTECT_ERR
                        FLASH_BUSY
                        FLASH_LOCKED
  */
extern flashStat FLASH_programHalfWord(u32 address, u16 val)
{
    flashStat status = FLASH_GetStatus();

    if( status == FLASH_BUSY )
    {
        FLASH_WaitForOperation();
        status = FLASH_GetStatus();
    }
    else if ( status == FLASH_LOCKED )
    {
        FLASH_unlock();
        status = FLASH_GetStatus();
    }

    if( status == FLASH_COMPLETE )
    {
        FPEC_peripheral->CR |= FLASH_CR_PG;
        *((u16 *)address) = val;
        FLASH_WaitForOperation();
        if ((*(u16*)address) != val)
        {
            status = FLASH_PROG_ERR;
        }
        FPEC_peripheral->CR &= ~FLASH_CR_PG;
    }
    return status;
}

/**
  * @brief  Erase flash page that contains a certain address
  *
  * @param  address : holds an address within the page to be erased
  *
  * @retval flashStat : a value of the following:
                        FLASH_COMPLETE
                        FLASH_PROG_ERR
                        FLASH_WPROTECT_ERR
                        FLASH_BUSY
                        FLASH_LOCKED
  */
extern flashStat FLASH_erasePage(u32 address)
{
    flashStat status = FLASH_GetStatus();

    if( status == FLASH_BUSY )
    {
        FLASH_WaitForOperation();
        status = FLASH_GetStatus();
    }
    else if ( status == FLASH_LOCKED )
    {
        FLASH_unlock();
        status = FLASH_GetStatus();
    }

    if( status == FLASH_COMPLETE )
    {
        FPEC_peripheral->CR |= FLASH_CR_PER;
        FPEC_peripheral->AR = address;
        FPEC_peripheral->CR |= FLASH_CR_STRT;
        FLASH_WaitForOperation();

        if ((*(u16*)address) != 0xFFFF)
        {
            status = FLASH_PROG_ERR;
        }
        FPEC_peripheral->CR &= ~FLASH_CR_PER;
    }
    return status;
}


/**
  * @brief  Erase entire flash
  *
  * @retval flashStat : a value of the following:
                        FLASH_COMPLETE
                        FLASH_PROG_ERR
                        FLASH_WPROTECT_ERR
                        FLASH_BUSY
                        FLASH_LOCKED
  */
extern flashStat FLASH_massErase(void)
{
    flashStat status = FLASH_GetStatus();

    if( status == FLASH_BUSY )
    {
        FLASH_WaitForOperation();
        status = FLASH_GetStatus();
    }
    else if ( status == FLASH_LOCKED )
    {
        FLASH_unlock();
        status = FLASH_GetStatus();
    }

    if( status == FLASH_COMPLETE )
    {
        FPEC_peripheral->CR |= FLASH_CR_MER;
        FPEC_peripheral->CR |= FLASH_CR_STRT;
        FLASH_WaitForOperation();
        FPEC_peripheral->CR &= ~FLASH_CR_MER;
    }

    return status;
}
