#include "pbdata.h"
//****��ѯ����״̬****************
char task_buff[500];         //�洢�����Ϣ
char task_time_buff[500];    //�洢�����Ϣ
//******����������***************
TaskHandle_t StartTask_Handler;   //��ʼ����  
TaskHandle_t LEDTask_Handler;     //LED����
TaskHandle_t UITask_Handler;      //UI����
TaskHandle_t SPEEDTask_Handler;   //��������
TaskHandle_t MOTOTask_Handler;    //�������
TaskHandle_t APITask_Handler;     //�������API����
TaskHandle_t APITIMETask_Handler; //�����ʱ���API����
//******************************************
//�������֣���ʼ�����ʼ��
//�������ܣ���ʼ������ϵͳ�ĵ�һ�������������ڳ�ʼ����������
//******************************************
void FreeRTOS_Task_Start(void)
{
  xTaskCreate(
							(TaskFunction_t )start_task,            //������ Ҫ�ͺ��涨��ĺ���������һ��
							(const char*    )"start_task",          //�������� �ͺ�������һ������
							(uint16_t       )START_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                  //���ݸ��������Ĳ���
							(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&StartTask_Handler     //���������Լ�����ľ������һ��
				     );                
   vTaskStartScheduler();          //����������� ��ʱֻ�п�ʼ����ֻ��ִ����1������
}	
//******************************************
//�������֣���ʼ����
//�������ܣ����ڳ�ʼ����������
//******************************************
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ��� �ٽ��������������жϣ�����Ĳ������ᱻ��Ϸ����ڴ����Ĺ����оͻῪʼִ��������
    //����LED����
    xTaskCreate(
								(TaskFunction_t )led_task,     	
								(const char*    )"led_task",   	
								(uint16_t       )LED_STK_SIZE, 
								(void*          )NULL,				
								(UBaseType_t    )LED_TASK_PRIO,	
								(TaskHandle_t*  )&LEDTask_Handler
							 );   
    //����UI����
    xTaskCreate(
								(TaskFunction_t )ui_task,     
								(const char*    )"ui_task",   
								(uint16_t       )UI_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )UI_TASK_PRIO,
								(TaskHandle_t*  )&UITask_Handler
							 );
    //����SPEED����
    xTaskCreate(
								(TaskFunction_t )speed_task,     
								(const char*    )"speed_task",   
								(uint16_t       )SPEED_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )SPEED_TASK_PRIO,
								(TaskHandle_t*  )&SPEEDTask_Handler
							 );  	 																
    //�����������
    xTaskCreate(
								(TaskFunction_t )moto_task,     
								(const char*    )"moto_task",   
								(uint16_t       )MOTO_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )MOTO_TASK_PRIO,
								(TaskHandle_t*  )&MOTOTask_Handler
							 ); 								 					 		  							
   //API��������
    xTaskCreate(
								(TaskFunction_t )api_task,     
								(const char*    )"api_task",   
								(uint16_t       )API_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )API_TASK_PRIO,
								(TaskHandle_t*  )&APITask_Handler
							 );  	

   //APIʱ���������
    xTaskCreate(
								(TaskFunction_t )apitime_task,     
								(const char*    )"apitime_task",   
								(uint16_t       )APITIME_STK_SIZE, 
								(void*          )NULL,
								(UBaseType_t    )APITIME_TASK_PRIO,
								(TaskHandle_t*  )&APITIMETask_Handler
							 );  												
																	
		vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//******************************************
//�������֣�LED����
//�������ܣ�ʵ�������ƹ��ܣ����ϵͳ�Ƿ�����
//******************************************
void led_task(void *pvParameters)
{
    while(1)
    {
      LED=~LED;	    //������
			Feed_dog();   //ι��
			ADC_Check1();
			vTaskDelay(200);   	
    }
}   
//******************************************
//�������֣�UI����
//�������ܣ�ʵ�ֲ���1���ܣ�ʵʱ��������ٶ�
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
//�������֣�SPEED����
//�������ܣ�ʵ�ֲ��ٹ��ܣ�ʵʱ��������ٶ�
//******************************************
void speed_task(void *pvParameters)
{
	while(1)
   {
		  vTaskDelay(10);   
    }
	
	 
	
}
//******************************************
//�������֣�MOTO����
//�������ܣ�
//******************************************
void moto_task(void *pvParameters)
{
    while(1)
    {    
			vTaskDelay(10); 	
    }
}
//******************************************
//�������֣��������API
//�������ܣ��������API����
//******************************************
void api_task(void *pvParameters)
{
//	u8 i=0;
//	UBaseType_t priority_n=0;   //���ȼ�
//	UBaseType_t task_n=0;       //��������
//	UBaseType_t task_n1=0;      //��������
//	TaskStatus_t *StatusArray=0;//�������״̬���ڴ�
//	TaskStatus_t *StatusArray1=0;//�������״̬���ڴ�
//	UBaseType_t task_stak_min=0; //��ʷ��С�����ջʣ��
//	
//	
//	
//	//********************��ѯ�������ȼ�*******************************************
//	priority_n=uxTaskPriorityGet(LED0Task_Handler);  //INCLUDE_uxTaskPriorityGet��1   ��ѯ�������ȼ�
//	printf("��ȡ���������ȼ�Ϊ%ld\r\n",priority_n);
// 
//	//********************�����������ȼ�*******************************************
//	vTaskPrioritySet(LED0Task_Handler,8);            //INCLUDE_vTaskPrioritySet��1 �����������ȼ�Ϊ8
//  priority_n=uxTaskPriorityGet(LED0Task_Handler);  //INCLUDE_uxTaskPriorityGet��1   ��ѯ�������ȼ�
//	printf("�޸ĺ���������ȼ�Ϊ%ld\r\n",priority_n);	
//	
//	//********************��ȡ��������*********************************************
//	task_n=uxTaskGetNumberOfTasks();                //��ȡ��������  ���˵���������  ��������  ��ʱ������  �������Զ�������+2
//	printf("��������Ϊ%ld\r\n",task_n);
////	
//	//********************��ȡ���е�����״̬***************************************
//	StatusArray=pvPortMalloc(task_n*sizeof(TaskStatus_t));//�����ڴ�
//	task_n1=uxTaskGetSystemState( StatusArray,task_n , NULL);//configUSE_TRACE_FACILITY��1
//	printf("������		�������ȼ�		������		��ʷʣ����Сֵ\r\n");
//	for(i=0;i<task_n1;i++)
//	{
//	  printf("%s		%ld		%ld		%d\r\n",
//		      StatusArray[i].pcTaskName,     
//		      StatusArray[i].uxCurrentPriority,
//		      StatusArray[i].xTaskNumber,
//		      StatusArray[i].usStackHighWaterMark
//		      );
//	}
//	vPortFree(StatusArray);	//�ͷ��ڴ�
//	
//	//********************��ȡָ���������Ϣ************************************
//	StatusArray1=pvPortMalloc(sizeof(TaskStatus_t));//�����ڴ�
//	//��ȡLED0_Task��������Ϣ
//	vTaskGetInfo(LED0Task_Handler, 		   //������
//				       StatusArray1, 		       //������Ϣ�ṹ��
//				       pdTRUE,			           //����ͳ�������ջ��ʷ��Сʣ���С
//			         eInvalid                //�����Լ���ȡ��������׳̬
//							);			        
//	//ͨ�����ڴ�ӡ��ָ��������й���Ϣ��
//	printf("������:                %s\r\n",StatusArray1->pcTaskName);
//	printf("������:              %d\r\n",(int)StatusArray1->xTaskNumber);
//	printf("����׳̬:              %d\r\n",StatusArray1->eCurrentState);
//	printf("����ǰ���ȼ�:        %d\r\n",(int)StatusArray1->uxCurrentPriority);
//	printf("��������ȼ�:          %d\r\n",(int)StatusArray1->uxBasePriority);
//	printf("�����ջ����ַ:        %#x\r\n",(int)StatusArray1->pxStackBase);
//	printf("�����ջ��ʷʣ����Сֵ:%d\r\n",StatusArray1->usStackHighWaterMark);
//	vPortFree(StatusArray1);	//�ͷ��ڴ�
//	
//	//***************��ȡָ������Ķ�ջ��ʷʣ����Сֵ****************************
//	 task_stak_min=uxTaskGetStackHighWaterMark(LED0Task_Handler);   //INCLUDE_uxTaskGetStackHighWaterMark��1
//	 printf("�����ջ��ʷʣ����Сֵ:%ld\r\n",task_stak_min);
//	 
//	//***************�Ա�����ʽ��ȡ�����е���Ϣ****************************
//	//configUSE_TRACE_FACILITY��1 configUSE_STATS_FORMATTING_FUNCTIONS��1
//	vTaskList(task_buff);       //B����̬ R����̬ S����̬ Dɾ��̬
//	printf("����           ״̬   ���ȼ�   ��Сֵ   ���\r\n");
//	printf("%s\r\n",task_buff);	
	while(1)
	{
	  vTaskDelay(10);	   
	}
}

//***********�Ա����ʽ��ʾ���������ʱ��*******************************
//configGENERATE_RUN_TIME_STATS��1  configUSE_STATS_FORMATTING_FUNCTIONS��1
//�����ã���������IDL��ռ��Խ��˵��CPUѹ��ԽС�������ռ�ȸ�˵�������Ӷȸߣ����Կ��ǲ��
//configGENERATE_RUN_TIME_STATS��1  ��Ҫ�Ѻ���portCONFIGURE_TIMER_FOR_RUN_TIME_STATS();���壬ʱ����ʱ����10-100��ʱ��Ƭ�ľ��ȣ���������10uS
//portGET_RUN_TIME_COUNTER_VALUE();���ڻ�ȡӲ������ֵ
//������ʹ��time3����10uS�жϼ�ʱ

void apitime_task(void *pvParameters)
{ 
	while(1)
	{   
//		vTaskGetRunTimeStats(task_time_buff);
//	  printf("����           ʱ��*10uS        ռ��\r\n");
//	  printf("%s\r\n",task_time_buff);
	  vTaskDelay(1000);	  
	}
}



























