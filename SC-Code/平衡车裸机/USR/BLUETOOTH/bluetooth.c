#include "pbdata.h"  
u8 USART3_MSG_flag=0;
u8 USART3_MSG_Value=0;
u8 USART3_Count=0;
u8 USART3_Cmd_Flag=0;       
u8 USART3_Receieve[8];  
u8 BT_Data1=0;
u8 BT_Data2=0;
//****************串口时钟****************************
void USART3_MSG_RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
}
//****************串口引脚************************************
void USART3_MSG_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//txd
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//rxd	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}	
//******************串口配置**********************************
void USART3_MSG_Configration(void)
{
	USART_InitTypeDef USART_InitStructure;                      
	USART_InitStructure.USART_BaudRate=115200;            
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                     
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
  USART_Init(USART3, &USART_InitStructure);                    
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);                
  USART_Cmd(USART3,ENABLE);                                    
  USART_ClearFlag(USART3,USART_FLAG_TC); 	
}
//*****************串口优先级**********************************
void USART3_MSG_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     	
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;            
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              
  NVIC_Init(&NVIC_InitStructure); 
}
//*********************串口初始化**********************************
void USART3_MSG_Init(void)
{
  USART3_MSG_RCC_Configuration();
  USART3_MSG_GPIO_Configuration();
  USART3_MSG_Configration();
  USART3_MSG_NVIC_Configuration();
}
//*********************串口中断********************************
void USART3_IRQHandler(void)
{ 
   if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET) 
	 {	
     USART3_MSG_flag=1;
	   USART3_MSG_Value=USART_ReceiveData(USART3);           		 
     USART3_Receieve[USART3_Count]=USART3_MSG_Value;         
		 USART3_Count++;			 
		 if(USART3_Count>7)        //一个包4个字节, 2*4-1=7                            
			{
				 USART3_Count=0;	
         USART3_Cmd_Flag=1;		       	
			}	
		 //USART_SendData(USART3,USART_MSG_Value);
		 while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	 }
}
//********************蓝牙发送数据专用************************************
void BT_Send(const char *Str)    
{ 
	   while ( *Str)
    {
        USART_SendData (USART3,*Str );
			  while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
        *Str++;
    }
}
//**********************串口3数据解码**********************
void Receive_BT_Data(void)
{ 
	u8 j;		
	 for(j=0;j<8;j++)
	{
	   if(USART3_Receieve[j]==0xFF)                     
		 {                                               
			 if(USART3_Receieve[j+3]==((USART3_Receieve[j+2]+USART3_Receieve[j+1]+USART3_Receieve[j])&0x00FF))  
			 {		 					 
					BT_Data1=USART3_Receieve[j+1];
					BT_Data2=USART3_Receieve[j+2];  			 
			 }
	   }
   }
	USART3_Count=0;	
}










