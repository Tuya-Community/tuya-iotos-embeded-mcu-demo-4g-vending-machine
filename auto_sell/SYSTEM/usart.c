#include "sys.h"
#include "usart.h"
#include "cellular.h"

//*****************************************USART3************PB10TXD PB11RXD***************************************//
void USART3_Init(uint32_t pclk2,uint32_t bound)
{  	 
	float temp;
	uint16_t mantissa;
	uint16_t fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
	mantissa<<=4;
	mantissa+=fraction; 

	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	RCC->APB1ENR|=1<<18;  //ʹ�ܴ���3ʱ�� 
	GPIOB->CRH&=~(0xf<<8|0xf<<12);
	GPIOB->CRH|=0X0B<<8|8<<12;//IO״̬����	  PB10TXD���ù����������ģʽ50MHz PB11RXD����/��������ģʽ
	GPIOB->ODR|=1<<11;

	RCC->APB1RSTR|=1<<18;   //��λ����3
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   	   
	//����������
	USART3->BRR=mantissa; // ����������	 
	USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.					  
	USART3->CR1|=1<<8;    //PE�ж�ʹ��
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(1,2,USART3_IRQn,2);//��2  			   ��ռ���ȼ� ��Ӧ���ȼ� �жϱ��  �жϷ��� 0~4

}

uint8_t Uart3_PutChar(uint8_t data)
{
	uint8_t ret=1;
	uint16_t timeout=0x8000;

	USART3->DR = data;
	while((USART3->SR&1<<6)!=1<<6)//�ȴ��������
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
	if(USART3->SR&(1<<5))//���յ�����
	{
		//DA=USART3->DR;
		uart_receive_input((unsigned char)(USART3->DR));
	}

} 	

