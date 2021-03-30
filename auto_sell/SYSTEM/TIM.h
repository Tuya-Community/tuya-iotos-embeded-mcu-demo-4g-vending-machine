#ifndef __TIM_H
#define __TIM_H 		

#include "stm32f10x.h"



extern uint8_t F_TASK_CHK_ALLOW;
void TIM2_Init(u16 arr,u16 psc);
void TIM2_Start(void);
void TIM2_Stop(void);
void TIM_Init(void);




#endif


