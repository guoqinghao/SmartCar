#include "pbdata.h"
int mpu_button=0;
//*****************MPU_INTʱ�ӳ�ʼ��********************
void MPU_INT_RCC_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
}
//*****************MPU_INT���ų�ʼ��********************
void MPU_INT_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
  //�������ж�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;            //PC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz  
	GPIO_Init(GPIOC, &GPIO_InitStructure);		
}
//***************���ð�ť�ж�************************
void MPU_INT_EINT_Init(void)
{
   EXTI_InitTypeDef  EXTI_InitStructure;	

	 EXTI_ClearITPendingBit(EXTI_Line6);                      
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
	 EXTI_InitStructure.EXTI_Line=EXTI_Line6;                
	 EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;        
	 EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;    
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;                
	 EXTI_Init(&EXTI_InitStructure); 
}
//***************���ð�ť���ȼ�************************
void MPU_INT_NVIC_Init(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;  

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             
		NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;   
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            
		NVIC_Init(&NVIC_InitStructure); 
}
//*****************MPU_INT��ʼ��************************
void MPU_INT_Init(void)
{
  MPU_INT_RCC_Init();
  MPU_INT_GPIO_Init();
	MPU_INT_EINT_Init();
	MPU_INT_NVIC_Init();
}
//****************�жϷ�����*********************************
void EXTI9_5_IRQHandler(void)             
{	
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)==0)
  { 

  }

	EXTI_ClearITPendingBit(EXTI_Line6);	
}





