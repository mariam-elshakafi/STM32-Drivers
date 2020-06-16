#include "STD_TYPES.h"
#include "SYSTICK.h"
#include "SYSTICK_CFG.h"


typedef struct
{
  u32 CTRL;
  u32 LOAD;
  u32 VAL;
  u32 CALIB;  
} SYSTICK_regMap;

#define SYSTICK_BASE_ADDRESS 0xE000E010
#define SYSTICK_peripheral ((volatile SYSTICK_regMap *) SYSTICK_BASE_ADDRESS)


#define SYSTICK_ENABLE_SETMASK  0x00000001
#define SYSTICK_TICKINT_SETMASK 0x00000002
#define SYSTICK_CLKSRC_SETMASK  0x00000004


static SYSTICK_cbF AppCbF = NULL;


void SYSTICK_init(void)
{
  (SYSTICK_peripheral->CTRL) |= SYSTICK_TICKINT_SETMASK;
  (SYSTICK_peripheral->CTRL) &= ~SYSTICK_CLKSRC_SETMASK;
  (SYSTICK_peripheral->CTRL) |= SYSTICK_CLKSRC_PRE;
}

void SYSTICK_start(void)
{
  (SYSTICK_peripheral->CTRL) |= SYSTICK_ENABLE_SETMASK;
}

void SYSTICK_stop(void)
{
  (SYSTICK_peripheral->CTRL) &= ~SYSTICK_ENABLE_SETMASK;
}

void SYSTICK_setTime(u32 timeMs, u32 AHB_clockHz)
{
  u32 clock = AHB_clockHz;
  if (((SYSTICK_peripheral->CTRL) & SYSTICK_CLKSRC_SETMASK) == SYSTICK_CLKSRC_AHB_DIV_8)
  {
    clock >>= 3;
  }
  
  f32 countFloat = timeMs * (clock/1000.0);
  u32 count = (u32)countFloat & 0x00FFFFFF;
  (SYSTICK_peripheral->LOAD) = count;
}

void SYSTICK_setCallbackFcn(SYSTICK_cbF cbF)
{
  if(cbF)
  {
    AppCbF = cbF;
  }
}

void SysTick_Handler(void)
{
  if(AppCbF)
  {
    AppCbF();
  }
}
