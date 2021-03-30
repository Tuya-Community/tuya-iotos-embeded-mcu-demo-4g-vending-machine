#include "TIM.h"
#include "sys.h"
#include "IO.h"
#include "usart.h"

void TIM2_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM2ʱ��ʹ��    
 	TIM2->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM2->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM2->DIER|=1<<0;   //��������ж�				
	TIM2->DIER|=1<<6;   //�������ж�	   
	TIM2->CR1|=0x01;    //ʹ�ܶ�ʱ��2
	MY_NVIC_Init(3,3,TIM2_IRQn,2);//��ռ3�������ȼ�3����2									 
}


void TIM2_Start(void)
{
	TIM2->CR1 |=1<<0;//ʹ�ܼ�����
}
void TIM2_Stop(void)
{
	TIM2->CR1 &=~(1<<0);	//��ֹ������
	TIM2->CNT =0;//��������
}
void TIM2_Continue(void)
{
	TIM2->CR1 |=1<<0;//ʹ�ܼ�����
	TIM2->CNT =0;//��������
}

uint8_t F_TASK_CHK_ALLOW=0;
void TIM2_IRQHandler(void)//
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{	
		F_TASK_CHK_ALLOW=1;
		TIM2_Stop();
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}

void Timer3_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3ʱ��ʹ��	
 	TIM3->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM3->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->DIER|=1<<6;   //�������ж�	   
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3
	MY_NVIC_Init(3,2,TIM3_IRQn,2);//��ռ3�������ȼ�2����2									 
}

void TIM3_IRQHandler(void)//
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{	
		//LED_TOG;
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}


void TIM4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM4ʱ��ʹ��    
 	TIM4->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM4->PSC=psc;  //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM4->DIER|=1<<0;   //��������ж�				
	TIM4->DIER|=1<<6;   //�������ж�	   
	TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��4
  	MY_NVIC_Init(3,1,TIM4_IRQn,2);//��ռ3�������ȼ�1����2									 
}
void TIM4_IRQHandler(void)//
{ 		    		  			    
	//uint8_t DATA[1]={0x55};
	if(TIM4->SR&0X0001)//����ж�
	{	
		F_TASK_KEY_CHK=1;
		//USART_Send(USART3,DATA,1);
		//Uart3_PutChar(DATA);
		if(F_TASK_CHK_ALLOW)
		{
			F_TASK_MOTOR_CHK=1;
		}
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}

//TimerX_Init(1000,7199);//��100ms��һ���ж� 1000->100MS
void TIM_Init(void)
{
	TIM2_Init(12,7199);//��λ�����ʱ����
	TIM2_Stop();
	TIM4_Init(1000,7199);//����+��λ���
}






