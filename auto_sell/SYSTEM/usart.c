#include "sys.h"
#include "usart.h"
#include "cellular.h"

//*****************************************USART3************PB10TXD PB11RXD***************************************//
void USART3_Init(uint32_t pclk2,uint32_t bound)
{  	 
	float temp;
	uint16_t mantissa;
	uint16_t fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
	mantissa<<=4;
	mantissa+=fraction; 

	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  //使能串口3时钟 
	GPIOB->CRH&=~(0xf<<8|0xf<<12);
	GPIOB->CRH|=0X0B<<8|8<<12;//IO状态设置	  PB10TXD复用功能推挽输出模式50MHz PB11RXD上拉/下拉输入模式
	GPIOB->ODR|=1<<11;

	RCC->APB1RSTR|=1<<18;   //复位串口3
	RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
	//波特率设置
	USART3->BRR=mantissa; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位.					  
	USART3->CR1|=1<<8;    //PE中断使能
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(1,2,USART3_IRQn,2);//组2  			   抢占优先级 响应优先级 中断编号  中断分组 0~4

}

uint8_t Uart3_PutChar(uint8_t data)
{
	uint8_t ret=1;
	uint16_t timeout=0x8000;

	USART3->DR = data;
	while((USART3->SR&1<<6)!=1<<6)//等待发送完毕
	{
		timeout--;
		if( 0 == timeout )
		{
			ret = 1;
			break;
		}
	}

	if( 0 != timeout )
	{
		ret = 0;
	}
	return ret;
}
void USART3_IRQHandler(void)
{
  //uint8_t DA;
	if(USART3->SR&(1<<5))//接收到数据
	{
		//DA=USART3->DR;
		uart_receive_input((unsigned char)(USART3->DR));
	}

} 	

