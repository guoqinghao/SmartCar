#ifndef _bluetooth_H
#define _bluetooth_H
#include "pbdata.h"
extern u8 USART3_MSG_flag;
extern u8 USART3_MSG_Value;
extern u8 USART3_Count;
extern u8 USART3_Cmd_Flag;       
extern u8 USART3_Receieve[8];  
extern u8 BT_Data1;
extern u8 BT_Data2;
void USART3_MSG_RCC_Configuration(void);
void USART3_MSG_GPIO_Configuration(void);
void USART3_MSG_Configration(void);
void USART3_MSG_NVIC_Configuration(void);
void USART3_MSG_Init(void);
void USART3_IRQHandler(void);
void BT_Send(const char *Str);
void Receive_BT_Data(void);
#endif

