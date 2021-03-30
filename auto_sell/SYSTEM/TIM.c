#include "TIM.h"
#include "sys.h"
#include "IO.h"
#include "usart.h"

void TIM2_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<0;//TIM2时钟使能    
 	TIM2->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM2->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东西要同时设置才可以使用中断
	TIM2->DIER|=1<<0;   //允许更新中断				
	TIM2->DIER|=1<<6;   //允许触发中断	   
	TIM2->CR1|=0x01;    //使能定时器2
	MY_NVIC_Init(3,3,TIM2_IRQn,2);//抢占3，子优先级3，组2									 
}


void TIM2_Start(void)
{
	TIM2->CR1 |=1<<0;//使能计数器
}
void TIM2_Stop(void)
{
	TIM2->CR1 &=~(1<<0);	//禁止计数器
	TIM2->CNT =0;//计数清零
}
void TIM2_Continue(void)
{
	TIM2->CR1 |=1<<0;//使能计数器
	TIM2->CNT =0;//计数清零
}

uint8_t F_TASK_CHK_ALLOW=0;
void TIM2_IRQHandler(void)//
{ 		    		  			    
	if(TIM2->SR&0X0001)//溢出中断
	{	
		F_TASK_CHK_ALLOW=1;
		TIM2_Stop();
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}

void Timer3_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;//TIM3时钟使能	
 	TIM3->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM3->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东西要同时设置才可以使用中断
	TIM3->DIER|=1<<0;   //允许更新中断				
	TIM3->DIER|=1<<6;   //允许触发中断	   
	TIM3->CR1|=0x01;    //使能定时器3
	MY_NVIC_Init(3,2,TIM3_IRQn,2);//抢占3，子优先级2，组2									 
}

void TIM3_IRQHandler(void)//
{ 		    		  			    
	if(TIM3->SR&0X0001)//溢出中断
	{	
		//LED_TOG;
	}				   
	TIM3->SR&=~(1<<0);//清除中断标志位 	    
}


void TIM4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM4时钟使能    
 	TIM4->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM4->PSC=psc;  //预分频器7200,得到10Khz的计数时钟
	//这两个东西要同时设置才可以使用中断
	TIM4->DIER|=1<<0;   //允许更新中断				
	TIM4->DIER|=1<<6;   //允许触发中断	   
	TIM4->CR1|=0x01;    //使能定时器4
  	MY_NVIC_Init(3,1,TIM4_IRQn,2);//抢占3，子优先级1，组2									 
}
void TIM4_IRQHandler(void)//
{ 		    		  			    
	//uint8_t DATA[1]={0x55};
	if(TIM4->SR&0X0001)//溢出中断
	{	
		F_TASK_KEY_CHK=1;
		//USART_Send(USART3,DATA,1);
		//Uart3_PutChar(DATA);
		if(F_TASK_CHK_ALLOW)
		{
			F_TASK_MOTOR_CHK=1;
		}
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}

//TimerX_Init(1000,7199);//即100ms进一次中断 1000->100MS
void TIM_Init(void)
{
	TIM2_Init(12,7199);//到位检测延时开关
	TIM2_Stop();
	TIM4_Init(1000,7199);//按键+到位检测
}






