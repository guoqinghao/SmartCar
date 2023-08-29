#include "pbdata.h"
u8 front_flag=0;      //前进命令
u8 back_flag=0;       //后退命令
u8 turn_left_flag=0;  //左转命令
u8 turn_right_flag=0; //右转命令
u8 stop_flag=0;       //停止命令
u8 voice_flag=0;      //音频播放命令
//*******数据分析*************************************
void MSG_Analyze_BT(void)
{
 //*****获取数据包准备分析***********************	
  if(USART3_Cmd_Flag==1)
	{
	  USART3_Cmd_Flag=0;   //数据包接收完成
		Receive_BT_Data();   //数据采集
	}	
	//******停车**********
	if(BT_Data1==0x01)
	{
		BT_Data1=0;
		stop_flag=1;	
		USART3_Count=0;
	}
	//******前进*********
	if(BT_Data1==0x02)
	{
		BT_Data1=0;
		front_flag=1;
		USART3_Count=0;
	}
	//******后退*******
	if(BT_Data1==0x03)
	{
		BT_Data1=0;
		back_flag=1;
		USART3_Count=0;
	}
	//******左转*********
	if(BT_Data1==0x04)
	{
		BT_Data1=0;
		turn_left_flag=1;
		USART3_Count=0;
	}
	//*****右转********
	if(BT_Data1==0x05)
	{
		BT_Data1=0;
		turn_right_flag=1;
		USART3_Count=0;
	}
	//*****音频播放*****
	if(BT_Data1==0x06)
	{
		BT_Data1=0;
		voice_flag=1;
		USART3_Count=0;
	}
}
//*********UI交互*********************************
void UI(void)
{
	 MSG_Analyze_BT();			//数据解码
  //*****停车************
	if(stop_flag==1)
	{
	  stop_flag=0;
		Movement=0;
		turnment=0;
		return;
	}
  //****前进************
	if(front_flag==1)
	{
	  front_flag=0;
		Movement=BT_Data2*10;
		return;
	}
  //****后退**********
	if(back_flag==1)
	{
	  back_flag=0;
		Movement=(-BT_Data2)*10;
		return;
	}
  //****左转*********
	if(turn_left_flag==1)
	{
	  turn_left_flag=0;
		turnment=(-BT_Data2)*10;
		return;
	}
  //***右转*********
	if(turn_right_flag==1)
	{
	  turn_right_flag=0;
		turnment=BT_Data2*10;
		return;
	}
  //***音频播放*******
	if(voice_flag==1)
	{
	  voice_flag=0;
	  Voice_File(BT_Data2);    
	  Voice_Start();          
		return;
	}
}
	
	
	


