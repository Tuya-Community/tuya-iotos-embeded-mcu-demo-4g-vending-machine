#ifndef __IO_H
#define __IO_H 		

//#include "stm32f10x.h"
#include"stdint.h"

//PA1 LED
#define LED_OUT {RCC->APB2ENR|=1<<2;GPIOA->CRL&=~(0xf<<4);GPIOA->CRL|=3<<4;} //推挽输出50MHZ
#define LED_SET GPIOA->ODR|=1<<1
#define LED_RESET  GPIOA->ODR&=~(1<<1)
#define LED_TOG GPIOA->ODR^=1<<1


//PA7 INDATA
#define INDATA_OUT {RCC->APB2ENR|=1<<2;GPIOA->CRL&=~((uint32_t)0xf<<28);GPIOA->CRL|=3<<28;} 
#define INDATA_SET GPIOA->ODR|=1<<7
#define INDATA_RESET  GPIOA->ODR&=~(1<<7)
#define INDATA_TOG GPIOA->ODR^=1<<7

//PC5 OEN
#define OEN_OUT {RCC->APB2ENR|=1<<4;GPIOC->CRL&=~(0xf<<20);GPIOC->CRL|=3<<20;} 
#define OEN_SET GPIOC->ODR|=1<<5
#define OEN_RESET  GPIOC->ODR&=~(1<<5)
#define OEN_TOG GPIOC->ODR^=1<<5

//PB0 LOCK
#define LOCK_OUT {RCC->APB2ENR|=1<<3;GPIOB->CRL&=~(0xf<<0);GPIOB->CRL|=3<<0;} 
#define LOCK_SET GPIOB->ODR|=1<<0
#define LOCK_RESET  GPIOB->ODR&=~(1<<0)
#define LOCK_TOG GPIOB->ODR^=1<<0

//PB1 SHIFT
#define SHIFT_OUT {RCC->APB2ENR|=1<<3;GPIOB->CRL&=~(0xf<<4);GPIOB->CRL|=3<<4;} 
#define SHIFT_SET GPIOB->ODR|=1<<1
#define SHIFT_RESET  GPIOB->ODR&=~(1<<1)
#define SHIFT_TOG GPIOB->ODR^=1<<1

//PB13 PL
#define PL_OUT {RCC->APB2ENR|=1<<3;GPIOB->CRH&=~(0xf<<20);GPIOB->CRH|=3<<20;} 
#define PL_SET GPIOB->ODR|=1<<13
#define PL_RESET  GPIOB->ODR&=~(1<<13)
#define PL_TOG GPIOB->ODR^=1<<13

//PB12 CP
#define CP_OUT {RCC->APB2ENR|=1<<3;GPIOB->CRH&=~(0xf<<16);GPIOB->CRH|=3<<16;} 
#define CP_SET GPIOB->ODR|=1<<12
#define CP_RESET  GPIOB->ODR&=~(1<<12)
#define CP_TOG GPIOB->ODR^=1<<12

//PB14 ODATA
#define ODATA_OUT {RCC->APB2ENR|=1<<3;GPIOB->CRH&=~(0xf<<24);GPIOB->CRH|=3<<24;} 
#define ODATA_IN {RCC->APB2ENR|=1<<3;GPIOB->CRH&=~(0xf<<24);GPIOB->CRH|=4<<24;} //输入
#define ODATA_SET GPIOB->ODR|=1<<14
#define ODATA_RESET  GPIOB->ODR&=~(1<<14)
#define ODATA_TOG GPIOB->ODR^=1<<14
#define ODATA ((GPIOB->IDR & 1<<14) == 1<<14)

//PC9 POWKEY
#define POWKEY_OUT {RCC->APB2ENR|=1<<4;GPIOC->CRH&=~(0xf<<4);GPIOC->CRH|=3<<4;} 
#define POWKEY_SET GPIOC->ODR|=1<<9
#define POWKEY_RESET  GPIOC->ODR&=~(1<<9)
#define POWKEY_TOG GPIOC->ODR^=1<<9

typedef enum {
	mot_null=0,
	mot_opening,
	mot_stop,
}mot_state;

extern uint8_t F_TASK_MOTOR;

void IO_Init(void);
void TASK_MOTOR(void);

typedef struct {
	uint8_t front;//队首指针
	uint8_t rear;//队尾指针
	uint8_t size;//队列容量
}Queue;
extern Queue Q_U3;

struct quene_buf
{
	uint8_t tab;
	uint16_t length;
	uint8_t data[6];
};	
extern struct quene_buf IoT_receive[5];

void front_inc(Queue* SQ);//队首指针
void rear_inc(Queue* SQ);//队尾指针

extern uint8_t MOTOR_NUM;
extern uint8_t THING_NUM[10];

extern uint8_t F_TASK_MOTOR_OPEN;
void TASK_MOTOR_OPEN(uint8_t NUM);

extern uint8_t F_TASK_MOTOR_STOP;
void TASK_MOTOR_STOP(void);

extern uint8_t F_TASK_MOTOR_CHK;
void TASK_MOTOR_CHK(void);

extern uint8_t F_TASK_KEY_CHK;	
void TASK_KEY_CHK(void);

extern uint8_t F_TASK_THING_FULL;	
void TASK_THING_FULL(void);
#endif


