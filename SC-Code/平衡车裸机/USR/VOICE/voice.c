#include "pbdata.h"     
u8 voice_n=0;   //音频播放标志位
//****************串口时钟****************************
void USART2_MSG_RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);      
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
}
//****************串口引脚************************************
void USART2_MSG_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);     //打开串口2的重映射
	//txd
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	//rxd	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}	
//******************串口配置**********************************
void USART2_MSG_Configration(void)
{
	USART_InitTypeDef USART_InitStructure;                      
	USART_InitStructure.USART_BaudRate=9600;            
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                     
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
  USART_Init(USART2, &USART_InitStructure);                    
  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                
  USART_Cmd(USART2,ENABLE);                                    
  USART_ClearFlag(USART2,USART_FLAG_TC); 	
}
//*****************串口优先级**********************************
void USART2_MSG_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;            
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              
  NVIC_Init(&NVIC_InitStructure); 
}
//*********************串口初始化**********************************
void USART2_MSG_Init(void)
{
  USART2_MSG_RCC_Configuration();
  USART2_MSG_GPIO_Configuration();
  USART2_MSG_Configration();
  USART2_MSG_NVIC_Configuration();
}
//*********************串口中断********************************
void USART2_IRQHandler(void)
{ 
	u8 aaa=0;
   if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET) 
	 {	
     aaa=USART_ReceiveData(USART2);     	 	 
		 USART_SendData(USART2,aaa);
		 while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	 }
}
//**************************音量强度0-30**************************
void Voice_Strength(u8 n)
{
  u8 sum=0;
	sum=0x04^0x31^n;
	USART_SendData(USART2,0x7E);   	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x04);   	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x31);   	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,n);      	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,sum);    	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0xEF);   	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
//**************************选择音频文件*************************
void Voice_File(u8 n)
{
  u8 sum=0;
	sum=0x05^0x41^n;
  USART_SendData(USART2,0x7E);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x05);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x41);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x00);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,n);				while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,sum);			while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0xEF);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
  delay_ms(100);
}
//**************************开始播放***********************
void Voice_Start(void)
{
	USART_SendData(USART2,0x7E);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x03);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x01);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x02);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0xEF);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}
//**************************暂停播放*************************
void Voice_Stop(void)
{
	USART_SendData(USART2,0x7E);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x03);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x02);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x01);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0xEF);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}

//**************************停止播放*************************
void Voice_Exit(void)
{
	USART_SendData(USART2,0x7E);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x03);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x0E);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0x0D);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	USART_SendData(USART2,0xEF);		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
}













