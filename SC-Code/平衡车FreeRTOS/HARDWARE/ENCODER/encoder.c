#include "pbdata.h"
//**********************±àÂëÆ÷Ê±ÖÓ³õÊ¼»¯*********************
void Encoder_Count_RCC(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
}
//**********************±àÂëÆ÷Òý½Å³õÊ¼»¯*********************
void Encoder_Count_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//**********TIM4,B6,B7****************
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	//**********TIM5,A0,A1****************
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
//**********************±àÂëÆ÷¹¦ÄÜ³õÊ¼»¯*********************
void Encoder_Count_Configuration(void)
{
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	//**********TIM4,B6,B7***********************************
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=65535;    //65536-1
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;     //1-1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM4,ENABLE);  
	//**********TIM5,A0,A1***********************************
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0xF;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInit(TIM5, &TIM_ICInitStruct);	
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=65535;    //65536-1
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;     //1-1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);
	TIM_Cmd(TIM5,ENABLE);  
}
//**********************±àÂëÆ÷³õÊ¼»¯*********************
void Encoder_Count_Init(void)
{
  Encoder_Count_RCC();
	Encoder_Count_GPIO();
	Encoder_Count_Configuration();
}
//******************±àÂëÆ÷Êý¾Ý¶ÁÈ¡********************************
int Encoder_Value(TIM_TypeDef* TIMx)
{ 
	int channal_val=0;
	
	channal_val = TIMx ->CNT;
	if(channal_val>>15)
	{			
		channal_val =  (channal_val&0x7FFF)-32767;
	}	
  return channal_val;
}
//****************±àÂëÆ÷ÇåÁã*************************************
void Encoder_Count_Clear(TIM_TypeDef* TIMx)
{
  TIMx ->CNT = 0;
}










