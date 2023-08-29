#ifndef __KEY_H
#define __KEY_H	 
#include "pbdata.h" 
extern int button;
void KEY_RCC_Init(void);
void KEY_GPIO_Init(void);
void KEY_EINT_Init(void);
void KEY_NVIC_Init(void);
void KEY_Init(void);	
void EXTI4_IRQHandler(void);
#endif

