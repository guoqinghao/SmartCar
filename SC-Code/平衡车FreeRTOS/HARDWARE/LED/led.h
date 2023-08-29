#ifndef __LED_H
#define __LED_H	 
#include "pbdata.h" 
#define LED PAout(5)	// PA5
void LED_RCC_Init(void);
void LED_GPIO_Init(void);
void LED_Init(void);//≥ı ºªØ		 				    
#endif

