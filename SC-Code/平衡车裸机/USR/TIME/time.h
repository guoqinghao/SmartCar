#ifndef _time_H
#define _time_H
#include "pbdata.h"
//******************定义变量***************************************
extern u16 time2;
extern u16 time7;
extern volatile unsigned long long FreeRTOSRunTimeTicks;
//**********************申明函数************************************
void ConfigureTimeForRunTimeStats(void);
void TIM2_RCC_Configuration(void);                //定时器时钟初始化
void TIM2_Configuration(void);                    //定时器中断函数配置
void TIM2_NVIC_Configuration(void);               //定时器优先级配置
void TIM2_IRQHandler(void);                       //定时器中断代码
void time2_init(void);                            //定时器初始化
void TIM7_RCC_Configuration(void);                //定时器时钟初始化
void TIM7_Configuration(void);                    //定时器中断函数配置
void TIM7_NVIC_Configuration(void);               //定时器优先级配置
void TIM7_IRQHandler(void);                       //定时器中断代码
void time7_init(void); 
#endif



