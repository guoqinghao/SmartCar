#ifndef _voice_H
#define _voice_H
#include "pbdata.h"
extern u8 voice_n;
void USART2_MSG_RCC_Configuration(void);
void USART2_MSG_GPIO_Configuration(void);
void USART2_MSG_Configration(void);
void USART2_MSG_Init(void);
void Voice_Strength(u8 n);
void Voice_File(u8 n);
void Voice_Start(void);
void Voice_Stop(void);
void Voice_Exit(void);
#endif

