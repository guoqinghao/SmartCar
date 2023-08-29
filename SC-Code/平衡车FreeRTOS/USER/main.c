#include "pbdata.h"
int main(void)
{
	uboot();               //系统启动函数
  OS_Init();             //系统驱动初始化
  FreeRTOS_Task_Start(); //操作系统开始运行
}



