#include "IO.h"
#include "delay.h"
#include "TIM.h"
#include "cellular.h"
//C1~C6		10~15
//L3~L10	0~7
//L1~L2		8~9
uint8_t MOTOR_STATE;
uint16_t MAIN_DATA=0;

void HC595Send(uint16_t data)
{
  uint8_t j;
	LOCK_RESET;
	delay_us(10);
  for (j = 16; j > 0; j--)
	{
    SHIFT_RESET;
		delay_us(10);
		
		if(data & 0x8000)
		{
		   INDATA_SET;
		}
		else
		{
			INDATA_RESET;
		}
		
		delay_us(10);
    data <<= 1;
    SHIFT_SET;
		delay_us(10);
  }
	LOCK_SET;
	delay_us(10);
}
uint8_t F_TASK_MOTOR_OPEN=0;
void TASK_MOTOR_OPEN(uint8_t NUM)//NUM��1��ʼ��10����
{
	//if(MOTOR_STATE==mot_stop)///&&(NUM>0)&&(NUM<11))
	{
		if(NUM>2)
			MAIN_DATA=1<<(NUM-3)|1<<10;
		else 
			MAIN_DATA=1<<(NUM+7)|1<<10;
		
		HC595Send(MAIN_DATA);
		MOTOR_STATE=mot_opening;
		NUM=0;
		TIM2_Start();//��ʼ��ʱ��1s��ʼ��λ���
		front_inc(&Q_U3);
		F_TASK_MOTOR_OPEN--;
	}
}
uint8_t F_TASK_MOTOR_STOP=0;	
void TASK_MOTOR_STOP(void)
{
	MAIN_DATA=0;
	HC595Send(MAIN_DATA);
	MOTOR_STATE=mot_stop;
	F_TASK_CHK_ALLOW=0;//��λ�󣬲����ж�
}

uint8_t F_TASK_MOTOR=0;
void TASK_MOTOR(void)
{
	if(MOTOR_STATE==mot_stop)
	{
		if((THING_NUM[IoT_receive[Q_U3.front].data[0]-1]==IoT_receive[Q_U3.front].data[1])&&(THING_NUM[IoT_receive[Q_U3.front].data[0]-1]>0))//����Ӧ
		{
			MOTOR_NUM=IoT_receive[Q_U3.front].data[0];
			IoT_receive[Q_U3.front].data[1]=IoT_receive[Q_U3.front].data[1]-1;//�������ݰ��еĿ������
			THING_NUM[IoT_receive[Q_U3.front].data[0]-1]=IoT_receive[Q_U3.front].data[1];//���¿��
			mcu_dp_raw_update(DPID_R_NUM,IoT_receive[Q_U3.front].data,6);
			TASK_MOTOR_OPEN(IoT_receive[Q_U3.front].data[0]);
		}
		else
		{
			IoT_receive[Q_U3.front].data[1]=THING_NUM[IoT_receive[Q_U3.front].data[0]-1];//��治��Ӧ���޿��
			mcu_dp_raw_update(DPID_R_NUM,IoT_receive[Q_U3.front].data,6);
			front_inc(&Q_U3);
			F_TASK_MOTOR_OPEN--;
		}
	}  

}



uint8_t HC165In(void)
{
	uint8_t i,dat=0;
	CP_SET;
	PL_RESET;
	delay_us(10);
	PL_SET;	
	delay_us(10);
	for(i=0;i<8;i++)
	{
		dat=dat<<1;
		if(ODATA==1)
		{
			dat=dat+1;
		}
		CP_RESET;
		delay_us(10);		
		CP_SET;
		delay_us(10);		
	}
	CP_RESET;
	return dat;
}
uint8_t F_TASK_MOTOR_CHK=0;	
void TASK_MOTOR_CHK(void)
{
	uint8_t HC165_data;
	HC165_data=HC165In();
	if(MOTOR_STATE==mot_opening)
	{
		if(HC165_data&0x02)//H1�͵�ƽ���������λ��IO�ڲɼ����ߵ�ƽ
		{
			F_TASK_MOTOR_STOP=1;
		}
	}
}

uint8_t MOTOR_NUM=0;//�����
#define THING_FULL 9
#define THING_EMPTY 0
uint8_t THING_NUM[10]={THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL,THING_FULL};//��Ʒ��,����9��
struct quene_buf IoT_receive[5];
Queue Q_U3;
void creat_sq(Queue* SQ)//���ö��в���
{
	SQ->front=0;
	SQ->rear=0;
	SQ->size=5;
}
void front_inc(Queue* SQ)//����ָ��
{
	SQ->front++;
	if(SQ->front==SQ->size)
	{
		SQ->front=0;
	}
}
void rear_inc(Queue* SQ)//��βָ��
{
	SQ->rear++;
	if(SQ->rear==SQ->size)
	{
		SQ->rear=0;
	}
}
uint8_t F_TASK_KEY_CHK=0;	
void TASK_KEY_CHK(void)
{
	uint8_t HC165_data;
	HC165_data=HC165In();
	if((HC165_data|0xFB)==0xFB)//�͵�ƽ������������
	{
		//��������
		LED_TOG;
		F_TASK_THING_FULL=1;
		//��������������ŵ������¼���
//		MOTOR_NUM1++;
//		if(MOTOR_NUM1==11)
//			MOTOR_NUM1=1;
//		MOTOR_NUM=MOTOR_NUM1;
//		F_TASK_MOTOR_OPEN=1;
	}
}
uint8_t F_TASK_THING_FULL=0;	
void TASK_THING_FULL(void)
{
	uint8_t i;
	for(i=0;i<10;i++)
	{
		THING_NUM[i]=THING_FULL;
	}
}
void TASK_THING_EMPTY(void)
{
	uint8_t i;
	for(i=0;i<10;i++)
	{
		THING_NUM[i]=THING_EMPTY;
	}
}


void IO_Init(void)
{
	LED_OUT;
	LED_SET;
	
	INDATA_OUT;
	INDATA_RESET;
	
	OEN_OUT;
	OEN_RESET;
	
	LOCK_OUT;//STCP
	LOCK_RESET;
	
	SHIFT_OUT;//SHCP
	SHIFT_RESET;
	
	TASK_MOTOR_STOP();
	
	PL_OUT;//SL�͵�ƽʹ��
	PL_SET;
	
	CP_OUT;//CLK,�����ش���
	ODATA_IN;//��������
	
	POWKEY_OUT;
	POWKEY_RESET;
	
	creat_sq(&Q_U3);
}
