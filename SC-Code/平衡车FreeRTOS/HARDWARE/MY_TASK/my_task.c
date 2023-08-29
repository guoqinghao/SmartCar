#include "pbdata.h"
//****查询任务状态****************
char task_buff[500];         //存储表格信息
char task_time_buff[500];    //存储表格信息
//******定义任务句柄***************
TaskHandle_t StartTask_Handler;   //开始任务  
TaskHandle_t LEDTask_Handler;     //LED任务
TaskHandle_t UITask_Handler;      //UI任务
TaskHandle_t SPEEDTask_Handler;   //测速任务
TaskHandle_t MOTOTask_Handler;    //电机任务
TaskHandle_t APITask_Handler;     //任务相关API任务
TaskHandle_t APITIMETask_Handler; //任务计时相关API任务
//******************************************
//函数名字：开始任务初始化
//函数功能：初始化操作系统的第一个任务函数，用于初始化其他任务
//******************************************
void FreeRTOS_Task_Start(void)
{
  xTaskCreate(
							(TaskFunction_t )start_task,            //任务函数 要和后面定义的函数的名字一样
							(const char*    )"start_task",          //任务名称 和函数名字一样就行
							(uint16_t       )START_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )START_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&StartTask_Handler     //任务句柄和自己定义的句柄名字一样
				     );                
   vTaskStartScheduler();          //开启任务调度 此时只有开始任务，只会执行这1个任务
}	
//******************************************
//函数名字：开始任务
//函数功能：用于初始化其他任务
//******************************************
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区 临界区屏蔽了所有中断，这里的操作不会被打断否则在创建的过程中就会开始执行任务了
    //创建LED任务
    xTaskCreate(
								(TaskFunction_t )led_task,     	
								(const char*    )"led_task",   	
								(uint16_t       )LED_STK_SIZE, 
								(void*          )NULL,				
								(UBaseType_t    )LED_TASK_PRIO,	
								(TaskHandle_t*  )&LEDTask_Handler
							 );   
    //创建UI任务
    xTaskCreate(
								(TaskFunction_t )ui_task,     
								(const char*    )"ui_task",   
								(uint16_t       )UI_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )UI_TASK_PRIO,
								(TaskHandle_t*  )&UITask_Handler
							 );
    //创建SPEED任务
    xTaskCreate(
								(TaskFunction_t )speed_task,     
								(const char*    )"speed_task",   
								(uint16_t       )SPEED_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )SPEED_TASK_PRIO,
								(TaskHandle_t*  )&SPEEDTask_Handler
							 );  	 																
    //创建电机任务
    xTaskCreate(
								(TaskFunction_t )moto_task,     
								(const char*    )"moto_task",   
								(uint16_t       )MOTO_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )MOTO_TASK_PRIO,
								(TaskHandle_t*  )&MOTOTask_Handler
							 ); 								 					 		  							
   //API测试任务
    xTaskCreate(
								(TaskFunction_t )api_task,     
								(const char*    )"api_task",   
								(uint16_t       )API_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )API_TASK_PRIO,
								(TaskHandle_t*  )&APITask_Handler
							 );  	

   //API时间测试任务
    xTaskCreate(
								(TaskFunction_t )apitime_task,     
								(const char*    )"apitime_task",   
								(uint16_t       )APITIME_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )APITIME_TASK_PRIO,
								(TaskHandle_t*  )&APITIMETask_Handler
							 );  												
																	
		vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//******************************************
//函数名字：LED任务
//函数功能：实现心跳灯功能，检测系统是否正常
//******************************************
void led_task(void *pvParameters)
{
    while(1)
    {
      LED=~LED;	    //心跳灯
			Feed_dog();   //喂狗
			ADC_Check1();
			vTaskDelay(200);   	
    }
}   
//******************************************
//函数名字：UI任务
//函数功能：实现测速1功能，实时检测轮子速度
//******************************************
void ui_task(void *pvParameters)
{
	 while(1)
    {   
			UI();			
			vTaskDelay(10);   	
    }
}
//******************************************
//函数名字：SPEED任务
//函数功能：实现测速功能，实时检测轮子速度
//******************************************
void speed_task(void *pvParameters)
{
	while(1)
   {
		  vTaskDelay(10);   
    }
	
	 
	
}
//******************************************
//函数名字：MOTO任务
//函数功能：
//******************************************
void moto_task(void *pvParameters)
{
    while(1)
    {    
			vTaskDelay(10); 	
    }
}
//******************************************
//函数名字：任务相关API
//函数功能：任务相关API测试
//******************************************
void api_task(void *pvParameters)
{
//	u8 i=0;
//	UBaseType_t priority_n=0;   //优先级
//	UBaseType_t task_n=0;       //任务数量
//	UBaseType_t task_n1=0;      //任务数量
//	TaskStatus_t *StatusArray=0;//存放任务状态的内存
//	TaskStatus_t *StatusArray1=0;//存放任务状态的内存
//	UBaseType_t task_stak_min=0; //历史最小任务堆栈剩余
//	
//	
//	
//	//********************查询任务优先级*******************************************
//	priority_n=uxTaskPriorityGet(LED0Task_Handler);  //INCLUDE_uxTaskPriorityGet置1   查询任务优先级
//	printf("获取的任务优先级为%ld\r\n",priority_n);
// 
//	//********************设置任务优先级*******************************************
//	vTaskPrioritySet(LED0Task_Handler,8);            //INCLUDE_vTaskPrioritySet置1 设置任务优先级为8
//  priority_n=uxTaskPriorityGet(LED0Task_Handler);  //INCLUDE_uxTaskPriorityGet置1   查询任务优先级
//	printf("修改后的任务优先级为%ld\r\n",priority_n);	
//	
//	//********************获取任务数量*********************************************
//	task_n=uxTaskGetNumberOfTasks();                //获取任务数量  个人的任务数量  空闲任务  定时器任务  所以是自定义数量+2
//	printf("任务数量为%ld\r\n",task_n);
////	
//	//********************获取所有的任务状态***************************************
//	StatusArray=pvPortMalloc(task_n*sizeof(TaskStatus_t));//申请内存
//	task_n1=uxTaskGetSystemState( StatusArray,task_n , NULL);//configUSE_TRACE_FACILITY置1
//	printf("任务名		任务优先级		任务编号		历史剩余最小值\r\n");
//	for(i=0;i<task_n1;i++)
//	{
//	  printf("%s		%ld		%ld		%d\r\n",
//		      StatusArray[i].pcTaskName,     
//		      StatusArray[i].uxCurrentPriority,
//		      StatusArray[i].xTaskNumber,
//		      StatusArray[i].usStackHighWaterMark
//		      );
//	}
//	vPortFree(StatusArray);	//释放内存
//	
//	//********************获取指定任务的信息************************************
//	StatusArray1=pvPortMalloc(sizeof(TaskStatus_t));//申请内存
//	//获取LED0_Task的任务信息
//	vTaskGetInfo(LED0Task_Handler, 		   //任务句柄
//				       StatusArray1, 		       //任务信息结构体
//				       pdTRUE,			           //允许统计任务堆栈历史最小剩余大小
//			         eInvalid                //函数自己获取任务运行壮态
//							);			        
//	//通过串口打印出指定任务的有关信息。
//	printf("任务名:                %s\r\n",StatusArray1->pcTaskName);
//	printf("任务编号:              %d\r\n",(int)StatusArray1->xTaskNumber);
//	printf("任务壮态:              %d\r\n",StatusArray1->eCurrentState);
//	printf("任务当前优先级:        %d\r\n",(int)StatusArray1->uxCurrentPriority);
//	printf("任务基优先级:          %d\r\n",(int)StatusArray1->uxBasePriority);
//	printf("任务堆栈基地址:        %#x\r\n",(int)StatusArray1->pxStackBase);
//	printf("任务堆栈历史剩余最小值:%d\r\n",StatusArray1->usStackHighWaterMark);
//	vPortFree(StatusArray1);	//释放内存
//	
//	//***************获取指定任务的堆栈历史剩余最小值****************************
//	 task_stak_min=uxTaskGetStackHighWaterMark(LED0Task_Handler);   //INCLUDE_uxTaskGetStackHighWaterMark置1
//	 printf("任务堆栈历史剩余最小值:%ld\r\n",task_stak_min);
//	 
//	//***************以表格的形式获取任务中的信息****************************
//	//configUSE_TRACE_FACILITY置1 configUSE_STATS_FORMATTING_FUNCTIONS置1
//	vTaskList(task_buff);       //B阻塞态 R就绪态 S挂起态 D删除态
//	printf("名字           状态   优先级   最小值   编号\r\n");
//	printf("%s\r\n",task_buff);	
	while(1)
	{
	  vTaskDelay(10);	   
	}
}

//***********以表格形式显示任务的运行时间*******************************
//configGENERATE_RUN_TIME_STATS置1  configUSE_STATS_FORMATTING_FUNCTIONS置1
//调试用，空闲任务IDL的占比越高说明CPU压力越小，任务的占比高说明任务复杂度高，可以考虑拆分
//configGENERATE_RUN_TIME_STATS置1  需要把函数portCONFIGURE_TIMER_FOR_RUN_TIME_STATS();定义，时基定时器用10-100倍时间片的精度，这里设置10uS
//portGET_RUN_TIME_COUNTER_VALUE();用于获取硬件计数值
//此例程使用time3进行10uS中断计时

void apitime_task(void *pvParameters)
{ 
	while(1)
	{   
//		vTaskGetRunTimeStats(task_time_buff);
//	  printf("名字           时间*10uS        占比\r\n");
//	  printf("%s\r\n",task_time_buff);
	  vTaskDelay(1000);	  
	}
}



























