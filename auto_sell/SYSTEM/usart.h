#ifndef __USART_H
#define __USART_H
//#include "stm32f10x.h"
//#include <stm32f10x_lib.h>
#include"stdint.h"
#include "stdio.h"	 


 
	  	
        	

void USART3_Init(uint32_t pclk2,uint32_t bound);
//uint8_t USART_Send(USART_TypeDef * MY_usart,uint8_t *data,uint16_t len);
uint8_t Uart3_PutChar(uint8_t ch);
#endif	   
















