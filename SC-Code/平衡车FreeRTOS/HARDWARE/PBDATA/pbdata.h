#ifndef _pbdata_H
#define _pbdata_H
#include "pbdata.h"
//****************************硬件相关*****************************
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_iwdg.h"
#include "misc.h"	 
#include "stm32f10x_tim.h"
#include "math.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
//*********************FreeRTOS相关********************************
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//*********************用户自定义相关******************************
#include "my_task.h"
#include "led.h"
#include "key.h"
#include "time.h"
#include "encoder.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "mpu6050.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "moto.h"
#include "pwm.h"
#include "pid.h"
#include "debug.h"
#include "adc.h"
#include "bluetooth.h"
#include "voice.h"
#include "flash_data.h"
#include "watch_dog.h"
#include "ui.h"
//****************************************************************
//0：默认开启校准，初始化需要把芯片放平，且以此时的状态为0
//1：关闭校准，以地球重力为基准，不需要放平芯片
//DMP稳定时间为8秒左右
#define CHECK_FLAG 1  
//陀螺仪采样频率，单位Hz
#define MPU_HZ 200
//陀螺仪IIC延时，计数值，不是毫秒
#define MPU_DELAY 1 
//****************************************************************
extern u8 mpu_dmp_flag;
extern int user_numbe;
//****************************************************************
void us(u16 time);   
void ms(u16 time);
void JTAG_IO_Init(void);
void uboot(void);
void OS_Init(void);       //系统初始化函数
#endif



