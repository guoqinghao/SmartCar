#include "pbdata.h"
//*****************LEDʱ�ӳ�ʼ��********************
void LED_RCC_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB�˿�ʱ��
}
//*****************LED���ų�ʼ��********************
void LED_GPIO_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //LED0-->PA.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					       //�����趨������ʼ��GPIOA.5
 GPIO_SetBits(GPIOA,GPIO_Pin_5);						           //PA.5 �����
}
//*****************LED��ʼ��************************
void LED_Init(void)
{
 LED_RCC_Init();
 LED_GPIO_Init();
}
 
