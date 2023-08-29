#ifndef _encoder_H
#define _encoder_H
#include "pbdata.h"
//**************************************************
void Encoder_Count_RCC(void);
void Encoder_Count_GPIO(void);
void Encoder_Count_Configuration(void);
void Encoder_Count_Init(void);
int Encoder_Value(TIM_TypeDef* TIMx);
void Encoder_Count_Clear(TIM_TypeDef* TIMx);
#endif


