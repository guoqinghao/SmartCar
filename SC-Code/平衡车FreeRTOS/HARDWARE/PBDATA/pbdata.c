#include "pbdata.h"
u8 mpu_dmp_flag=0;    //陀螺仪初始化判断
int user_number=0;    //用户开机次数判断
//**********************不精确微妙延时*****************************
void us(u16 time) 
{ u16 i=0;    
  while(time--)   
 {       
  i=10;     
  while(i--);       
 } 
} 
//***********************不精确毫秒延时****************************
void ms(u16 time) 
{ 
  u16 i=0;    
  while(time--)   
 {      
  i=12000;       
 while(i--);      
 } 
} 
//******************JTAG引脚复用取消******************************
//说明：
//JTAG复用取消只能调用一次语句，否则死机。并且初始化的GPIO要放在所有GPIO初始化的后面
//建议单独处理
//****************************************************************
void JTAG_IO_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;	
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
				
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;          
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;            
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;           
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}
//**************系统启动函数***************************
void uboot(void)
{
  SystemInit();                                  //系统初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4  
  JTAG_IO_Init();                                //解除仿真引脚复用
	delay_init();	    				                     //延时函数初始化
	USART3_MSG_Init();                             //蓝牙串口初始化
	USART2_MSG_Init();                             //音频串口初始化 
  ms(200);                                       //延时1秒，电源稳定后开机
  GPIO_SetBits(GPIOA,GPIO_Pin_3);                //锁死开机引脚，系统开机
	user_number=user_n_read();                     //读取用户开机次数
	if((user_number>=0xFFFFFFFE)||(user_number<0))
	{
	  user_number=0;
		voice_n=3;              //初次见面语音提示
    Voice_File(voice_n);    //播放语音	
	  Voice_Start();          //播放语音		
	}
	if(user_number<3)
	{
	  user_number++;
		user_n_write(user_number);      //写入最新次数
		BT_Send("AT+CN01\r\n");         //关闭蓝牙芯片提示音
		delay_ms(1000);			
		BT_Send("AT+BDSmart-Car\r\n");      //修改音频蓝牙名字
		delay_ms(1000);
		BT_Send("AT+CR00\r\n");         //关闭蓝牙回传
		delay_ms(1000);  	 
		BT_Send("AT+BMSmart-Car-Data\r\n"); //修改数据蓝牙名字
		delay_ms(1000);	
		BT_Send("AT+CA00\r\n"); 	      //设置音频蓝牙音量为0
		delay_ms(1000);	 
		BT_Send("AT+CZ\r\n");           //复位蓝牙芯片，显示新名字
		delay_ms(1000);	
	} 	
}
//********************************************************************
//                 系统初始化函数
//********************************************************************
/*
建议将所有优先级位都指定为抢占优先级位， 不保留任何优先级位作为子优先级位。 
任何其他配置都会 使 configMAX_SYSCALL_interrupt_PRIORITY 
设置与 分配给各个外设中断之间的直接关系复杂化。 
大多数系统的默认配置都是所需要的， STM32 驱动器库除外。 
如果您使用 STM32 和 STM32 驱动器库， 
请通过 调用 NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 ) 
来确保所有优先级位都被指定为抢占优先级位，这一步需要 在启动 RTOS 前完成。
*/
void OS_Init(void)
{ 	
	  USART1_MSG_Init();					                   //串口初始化
	  LED_Init();		  					                     //LED初始化
	  KEY_Init();                                    //KEY初始化  
	  Encoder_Count_Init();                          //编码器初始化
		PWM_Init();                                    //PWM初始化
    pid_init();                                    //PID参数初始化
	  debug_init();                                  //debug初始化	  
	  ADC_Check_Init();                              //ADC初始化	 
	  Voice_Strength(30);                            //音量设置30
	  delay_ms(100);
		MPU_Init();					                           //初始化MPU6050
	  mpu_dmp_flag=mpu_dmp_init();                   //初始化MPU6050的DMP  
    while(mpu_dmp_flag)                            //初始化成功后执行后面程序
		{
		  voice_n=1;            //初始化失败语音提示
			Voice_File(voice_n);  //选择文件
			Voice_Start();        //播放语音
		}			
	  voice_n=2;              //初始化成功语音提示
    Voice_File(voice_n);    //播放语音	
	  Voice_Start();          //播放语音	
    time2_init();                                  //定时器2初始化
	  time7_init();                                  //定时器4初始化	
    WATCH_DOG_Init();      												 //初始化看门狗		
}



































