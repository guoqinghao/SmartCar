#include "pbdata.h"
u8 front_flag=0;      //ǰ������
u8 back_flag=0;       //��������
u8 turn_left_flag=0;  //��ת����
u8 turn_right_flag=0; //��ת����
u8 stop_flag=0;       //ֹͣ����
u8 voice_flag=0;      //��Ƶ��������
//*******���ݷ���*************************************
void MSG_Analyze_BT(void)
{
 //*****��ȡ���ݰ�׼������***********************	
  if(USART3_Cmd_Flag==1)
	{
	  USART3_Cmd_Flag=0;   //���ݰ��������
		Receive_BT_Data();   //���ݲɼ�
	}	
	//******ͣ��**********
	if(BT_Data1==0x01)
	{
		BT_Data1=0;
		stop_flag=1;	
		USART3_Count=0;
	}
	//******ǰ��*********
	if(BT_Data1==0x02)
	{
		BT_Data1=0;
		front_flag=1;
		USART3_Count=0;
	}
	//******����*******
	if(BT_Data1==0x03)
	{
		BT_Data1=0;
		back_flag=1;
		USART3_Count=0;
	}
	//******��ת*********
	if(BT_Data1==0x04)
	{
		BT_Data1=0;
		turn_left_flag=1;
		USART3_Count=0;
	}
	//*****��ת********
	if(BT_Data1==0x05)
	{
		BT_Data1=0;
		turn_right_flag=1;
		USART3_Count=0;
	}
	//*****��Ƶ����*****
	if(BT_Data1==0x06)
	{
		BT_Data1=0;
		voice_flag=1;
		USART3_Count=0;
	}
}
//*********UI����*********************************
void UI(void)
{
	 MSG_Analyze_BT();			//���ݽ���
  //*****ͣ��************
	if(stop_flag==1)
	{
	  stop_flag=0;
		Movement=0;
		turnment=0;
		return;
	}
  //****ǰ��************
	if(front_flag==1)
	{
	  front_flag=0;
		Movement=BT_Data2*10;
		return;
	}
  //****����**********
	if(back_flag==1)
	{
	  back_flag=0;
		Movement=(-BT_Data2)*10;
		return;
	}
  //****��ת*********
	if(turn_left_flag==1)
	{
	  turn_left_flag=0;
		turnment=(-BT_Data2)*10;
		return;
	}
  //***��ת*********
	if(turn_right_flag==1)
	{
	  turn_right_flag=0;
		turnment=BT_Data2*10;
		return;
	}
  //***��Ƶ����*******
	if(voice_flag==1)
	{
	  voice_flag=0;
	  Voice_File(BT_Data2);    
	  Voice_Start();          
		return;
	}
}
	
	
	


