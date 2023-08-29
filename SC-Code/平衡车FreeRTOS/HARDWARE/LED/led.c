#include "pbdata.h"
//*****************LED时钟初始化********************
void LED_RCC_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
}
//*****************LED引脚初始化********************
void LED_GPIO_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED0-->PA.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					       //根据设定参数初始化GPIOA.5
 GPIO_SetBits(GPIOA,GPIO_Pin_5);						           //PA.5 输出高
}
//*****************LED初始化************************
void LED_Init(void)
{
 LED_RCC_Init();
 LED_GPIO_Init();
}
 
