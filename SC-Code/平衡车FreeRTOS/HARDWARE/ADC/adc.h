#ifndef _ADC_H
#define _ADC_H
#include "pbdata.h"
extern float adt1;
extern float Bat_Value;
extern u8 Bat_n;
extern u8 tmp_value;
extern u8 adc_time_flag;
void ADC_RCC(void);                     //ADC时钟配置
void ADC_GPIO(void);                    //ADC管脚配置
void ADC_Configuration(void);           //ADC系统配置
void ADC_Check_Init(void);              //ADC初始化函数
void ADC_Check1(void);                  //ADC检测函数
void Temperature_check(void);
void Bat_energy(void);                  //电池电量检测 
#endif
































