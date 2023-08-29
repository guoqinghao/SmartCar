#ifndef __MY_TASK_H
#define __MY_TASK_H	 
#include "pbdata.h"
//*******�������ȼ�0-31,Խ��Խ����*******************
#define START_TASK_PRIO		    1        
#define LED_TASK_PRIO		      2
#define UI_TASK_PRIO		      3
#define SPEED_TASK_PRIO		    3
#define MOTO_TASK_PRIO		    3
#define API_TASK_PRIO		      2
#define APITIME_TASK_PRIO     2
//*******�����ջ��С	��λ�� *4�ĵ�λΪ�ֽ� 1024�ֽ�Ϊ1KB**********
#define START_STK_SIZE 		50     
#define LED_STK_SIZE 		  500  
#define UI_STK_SIZE       500  
#define SPEED_STK_SIZE    500 
#define MOTO_STK_SIZE 		500  
#define API_STK_SIZE 		  50 
#define APITIME_STK_SIZE 	50 
//****��ѯ����״̬****************
extern char task_buff[500];    //�洢�����Ϣ
extern char task_time_buff[500];
//********������*******************
extern TaskHandle_t StartTask_Handler;     
extern TaskHandle_t LEDTask_Handler;
extern TaskHandle_t UITask_Handler;
extern TaskHandle_t SPEEDTask_Handler;
extern TaskHandle_t MOTOTask_Handler;
extern TaskHandle_t APITask_Handler;
extern TaskHandle_t APITIMETask_Handler;
//********������*******************
void FreeRTOS_Task_Start(void);
void start_task(void *pvParameters);
void led_task(void *pvParameters);
void ui_task(void *pvParameters);	
void speed_task(void *pvParameters);	
void moto_task(void *pvParameters);	
void api_task(void *pvParameters);
void apitime_task(void *pvParameters);
#endif
