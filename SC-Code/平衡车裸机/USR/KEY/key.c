#include "pbdata.h"
int button=0;
//*****************KEYʱ�ӳ�ʼ��********************
void KEY_RCC_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
}
//*****************KEY���ų�ʼ��********************
void KEY_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
	//����������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				     //LED0-->PA.3 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					     //�����趨������ʼ��GPIOA.3	
  //����,�ж�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            //PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
//***************���ð�ť�ж�************************
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
//***************���ð�ť���ȼ�************************
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
//*****************KEY��ʼ��************************
void KEY_Init(void)
{
  KEY_RCC_Init();
  KEY_GPIO_Init();
	KEY_EINT_Init();
	KEY_NVIC_Init();
}
//****************�жϷ�����*********************************
void EXTI4_IRQHandler(void)             
{	
	delay_ms(20);   //��������
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
  { 
    //button++;
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);	 //�ػ�	
  }

	EXTI_ClearITPendingBit(EXTI_Line4);	
} 




