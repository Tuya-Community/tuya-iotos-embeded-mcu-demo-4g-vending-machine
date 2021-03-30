#include "sys.h"
#include "delay.h"
#include "usart.h"		
#include "IO.h"
#include "TIM.h"
#include "cellular.h"



int main()
{
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	IO_Init();
	TIM_Init();
	USART3_Init(36,115200); //串口3初始化 
	delay_ms(500);
	TIM2_Init(12000,7199);//到位检测延时开关
	TIM2_Stop();
	F_TASK_CHK_ALLOW=0;
	F_TASK_MOTOR_CHK=0;
	POWKEY_SET;
	cellular_protocol_init();
	while(1)
	{	   
		cellular_uart_service();
		
		if(F_TASK_MOTOR_STOP)
		{
			F_TASK_MOTOR_STOP=0;
			TASK_MOTOR_STOP();
		}
		if(F_TASK_MOTOR_OPEN)
		{
			//TASK_MOTOR_OPEN(MOTOR_NUM);//转动对应电机，并将MOTOR_NUM清零
			TASK_MOTOR();
		}
		if(F_TASK_MOTOR_CHK)
		{
			F_TASK_MOTOR_CHK=0;
			TASK_MOTOR_CHK();
		}
		if(F_TASK_KEY_CHK)
		{
			F_TASK_KEY_CHK=0;
			TASK_KEY_CHK();
		}
		if(F_TASK_THING_FULL)
		{
			F_TASK_THING_FULL=0;
			TASK_THING_FULL();
		}		
	}		
}
#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
