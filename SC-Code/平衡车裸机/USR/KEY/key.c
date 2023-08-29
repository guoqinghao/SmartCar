#include "pbdata.h"
int button=0;
//*****************KEY时钟初始化********************
void KEY_RCC_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
}
//*****************KEY引脚初始化********************
void KEY_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
	//开机自锁引脚配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				     //LED0-->PA.3 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					     //根据设定参数初始化GPIOA.3	
  //按键,中断
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            //PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
//***************配置按钮中断************************
void KEY_EINT_Init(void)
{
   EXTI_InitTypeDef  EXTI_InitStructure;	
 
	 EXTI_ClearITPendingBit(EXTI_Line4);                      
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
	 EXTI_InitStructure.EXTI_Line=EXTI_Line4;                
	 EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;        
	 EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;    
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;                
	 EXTI_Init(&EXTI_InitStructure); 
}
//***************配置按钮优先级************************
void KEY_NVIC_Init(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;  
	 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    
		NVIC_InitStructure.NVIC_IRQChannel =EXTI4_IRQn;          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            
		NVIC_Init(&NVIC_InitStructure); 
}
//*****************KEY初始化************************
void KEY_Init(void)
{
  KEY_RCC_Init();
  KEY_GPIO_Init();
	KEY_EINT_Init();
	KEY_NVIC_Init();
}
//****************中断服务函数*********************************
void EXTI4_IRQHandler(void)             
{	
	delay_ms(20);   //按键消抖
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
  { 
    //button++;
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);	 //关机	
  }

	EXTI_ClearITPendingBit(EXTI_Line4);	
} 




