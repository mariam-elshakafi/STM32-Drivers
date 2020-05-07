/* Masks to be used in SYSTICK_CONF.h : SYSTICK_CLK_SRC */
#define SYSTICK_CLKSRC_AHB_DIV_8  0x00000000
#define SYSTICK_CLKSRC_AHB        0x00000004



typedef void (*SYSTICK_cbF)(void);


void SYSTICK_init(void);
void SYSTICK_start(void);
void SYSTICK_stop(void);
void SYSTICK_setTime(u32 timeMs, u32 AHB_clockHz);
void SYSTICK_setCallbackFcn(SYSTICK_cbF cbF);