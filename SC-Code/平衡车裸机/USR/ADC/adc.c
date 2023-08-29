#include "pbdata.h"
float adt1=0;        //ADC原始值
float Bat_Value=0;   //电池电压
u8 Bat_n=0;          //电池电量档位
u8 tmp_value=0;      //温度值
u8 adc_time_flag=0;  //定时监测电池电量
//**********************配置系统时钟*********************************
void ADC_RCC(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ADC PC4端口时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//打开ADC功能的时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);                   //对ADC专用时钟进行6分频12MHz
}
//**********************配置GPIO管脚*********************************
void ADC_GPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //ADC管脚配置 PC4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //模拟量输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}	
//**************************ADC配置函数**********************************
void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;                            //定义结构体变量
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;            //独立模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                 //单通道扫描模式
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;           //单次循环，只采集一次
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//采用软件触发模式
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //采用右对齐模式
  ADC_InitStructure.ADC_NbrOfChannel = 2;                       //只用了2个通道所以赋值为2
	ADC_TempSensorVrefintCmd(ENABLE);                             //开启内部温度传感器
  ADC_Init(ADC1, &ADC_InitStructure);                           //ADC初始化
  //规则组配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14,1, ADC_SampleTime_239Cycles5); //使用ADC1的通道14，采样周期为239.5   
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16,2, ADC_SampleTime_239Cycles5); //使用ADC1的通道16，采样周期为239.5 	
  ADC_Cmd(ADC1,ENABLE);                                         //使能ADC
  //校准ADC
	ADC_ResetCalibration(ADC1);                                   //先复位ADC
	while(ADC_GetResetCalibrationStatus(ADC1));                   //判断是否复位完成，完成以后才执行下一步
	ADC_StartCalibration(ADC1);                                   //开始指定ADC的校准状态
	while(ADC_GetCalibrationStatus(ADC1));                        //判断是否已经校准
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);                       //校准结束，开启使能
}
//*********************ADC初始化函数**************************************
void ADC_Check_Init(void)
{
  ADC_RCC(); 
  ADC_GPIO();	
	ADC_Configuration();
}
//*********************ADC检测控制函数**************************************
void ADC_Check1(void)
{
  	u32 ad=0;                    //初始化ad变量
	  u8 i;
	  float ad_value=0;
	  ADC_RegularChannelConfig(ADC1,14, 1, ADC_SampleTime_239Cycles5 );
		for(i=0;i<10;i++)           //循环50次求平均值
		{
		 ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //校准结束，开启使能
		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//对使能标志取反，因为转换结束标志为1，while（0）；才可以继续执行。判断是否转换结束
		 ad=ad+ADC_GetConversionValue(ADC1);	    //对采样的数值进行累加			
		}
		ad=ad/10;                                 //取平均数
		adt1=3.285/4095*ad;                         //AD采样到的实际电压
		ad_value=adt1*1.566667;                   //电阻分压换算出电池电压
		Bat_Value=ad_value;
}
//*********************温度检测函数**************************************
void Temperature_check(void)
{
  	u32 ad=0;                    //初始化ad变量
	  float tmp_num=0;
	  u8 i;
	  ADC_RegularChannelConfig(ADC1,16, 1, ADC_SampleTime_239Cycles5 );
		for(i=0;i<10;i++)           //循环50次求平均值
		{
		 ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //校准结束，开启使能
		 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//对使能标志取反，因为转换结束标志为1，while（0）；才可以继续执行。判断是否转换结束
		 ad=ad+ADC_GetConversionValue(ADC1);	    //对采样的数值进行累加			
		}
		ad=ad/10;                                 //取平均数
		tmp_num=3.285/4095*ad;
		tmp_value=((1.43-tmp_num)/0.0043+25)/1.3;      //实际温度
}
//***********************电池电量计算*******************************************
void Bat_energy(void)
{
  ADC_Check1();
	if(Bat_Value<3.2)
	{
	  Bat_n = 1;
	}

}


































