/**
 * @file FLASH.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the user interface for the Flash driver
 * @version 0.1
 * @date 2020-05-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef FLASH_H
#define FLASH_H

typedef u8 flashStat;

#define FLASH_COMPLETE       0
#define FLASH_PROG_ERR       1
#define FLASH_WPROTECT_ERR   2
#define FLASH_BUSY           3
#define FLASH_LOCKED         4


/**
  * @brief  Perform flash lock
  *
  */
void FLASH_lock(void);


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
extern flashStat FLASH_programHalfWord(u32 address, u16 val);


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
extern flashStat FLASH_erasePage(u32 address);


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
extern flashStat FLASH_massErase(void);

#endif