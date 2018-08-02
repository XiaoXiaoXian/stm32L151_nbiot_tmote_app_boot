/**
  *********************************************************************************************************
  * @file    delay.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-23
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "delay.h"
#include "sys.h"
#include "hal_iwdg.h"

#if SYSTEM_SUPPORT_OS													//���ʹ��OS, ����������ͷ�ļ�����ucosΪ��������
#include "includes.h"													//֧��OSʱʹ��
#endif


static u32 fac_us = 0;													//us��ʱ������

#if SYSTEM_SUPPORT_OS
static u16 fac_ms = 0;													//ms��ʱ������,��os��,����ÿ�����ĵ�ms��
#endif

#if SYSTEM_SUPPORT_OS													//���SYSTEM_SUPPORT_OS������,˵��Ҫ֧��OS��(������UCOS)
//��delay_us/delay_ms��Ҫ֧��OS��ʱ����Ҫ������OS��صĺ궨��ͺ�����֧��
//������3���궨��:
//	delay_osrunning	: ���ڱ�ʾOS��ǰ�Ƿ���������,�Ծ����Ƿ����ʹ����غ���
//	delay_ostickspersec	: ���ڱ�ʾOS�趨��ʱ�ӽ���,delay_init�����������������ʼ��systick
//	delay_osintnesting	: ���ڱ�ʾOS�ж�Ƕ�׼���,��Ϊ�ж����治���Ե���,delay_msʹ�øò����������������
//Ȼ����3������:
//	delay_osschedlock	: ��������OS�������,��ֹ����
//	delay_osschedunlock	: ���ڽ���OS�������,���¿�������
//	delay_ostimedly	: ����OS��ʱ,���������������

//�����̽���UCOSII��UCOSIII��֧��,����OS,�����вο�����ֲ
//֧��UCOSII
#ifdef	OS_CRITICAL_METHOD												//OS_CRITICAL_METHOD������,˵��Ҫ֧��UCOSII
#define delay_osrunning		OSRunning										//OS�Ƿ����б��,0,������; 1,������
#define delay_ostickspersec	OS_TICKS_PER_SEC								//OSʱ�ӽ���,��ÿ����ȴ���
#define delay_osintnesting 	OSIntNesting									//�ж�Ƕ�׼���,���ж�Ƕ�״���
#endif

//֧��UCOSIII
#ifdef 	CPU_CFG_CRITICAL_METHOD											//CPU_CFG_CRITICAL_METHOD������,˵��Ҫ֧��UCOSIII
#define delay_osrunning		OSRunning										//OS�Ƿ����б��,0,������;1,������
#define delay_ostickspersec	OSCfg_TickRate_Hz								//OSʱ�ӽ���,��ÿ����ȴ���
#define delay_osintnesting 	OSIntNestingCtr								//�ж�Ƕ�׼���,���ж�Ƕ�״���
#endif


/**********************************************************************************************************
 @Function			void delay_osschedlock(void)
 @Description			us����ʱʱ,�ر��������(��ֹ���us���ӳ�)
 @Input				void
 @Return				void
**********************************************************************************************************/
void delay_osschedlock(void)
{
#ifdef CPU_CFG_CRITICAL_METHOD										//ʹ��UCOSIII
	OS_ERR err;
	OSSchedLock(&err);													//UCOSIII�ķ�ʽ,��ֹ����,��ֹ���us��ʱ
#else															//����UCOSII
	OSSchedLock();														//UCOSII�ķ�ʽ,��ֹ����,��ֹ���us��ʱ
#endif
}

/**********************************************************************************************************
 @Function			void delay_osschedunlock(void)
 @Description			us����ʱʱ,�ָ��������
 @Input				void
 @Return				void
**********************************************************************************************************/
void delay_osschedunlock(void)
{
#ifdef CPU_CFG_CRITICAL_METHOD										//ʹ��UCOSIII
	OS_ERR err; 
	OSSchedUnlock(&err);												//UCOSIII�ķ�ʽ,�ָ�����
#else															//����UCOSII
	OSSchedUnlock();													//UCOSII�ķ�ʽ,�ָ�����
#endif
}

/**********************************************************************************************************
 @Function			void delay_ostimedly(u32 ticks)
 @Description			����OS�Դ�����ʱ������ʱ
 @Input				ticks	: ��ʱ�Ľ�����
 @Return				void
**********************************************************************************************************/
void delay_ostimedly(u32 ticks)
{
#ifdef CPU_CFG_CRITICAL_METHOD
	OS_ERR err;
	OSTimeDly(ticks, OS_OPT_TIME_PERIODIC, &err);						//UCOSIII��ʱ��������ģʽ
#else
	OSTimeDly(ticks);												//UCOSII��ʱ
#endif 
}


/**********************************************************************************************************
 @Function			void SysTick_Handler(void)
 @Description			systick�жϷ�����,ʹ��OSʱ�õ�
 @Input				void
 @Return				void
**********************************************************************************************************/
void SysTick_Handler(void)
{
	HAL_IncTick();
	if (delay_osrunning == 1)											//OS��ʼ����,��ִ�������ĵ��ȴ���
	{
		OSIntEnter();													//�����ж�
		OSTimeTick();													//����ucos��ʱ�ӷ������
		OSIntExit();													//���������л����ж�
	}
}
#endif

/**********************************************************************************************************
 @Function			void Delay_Init(u8 SYSCLK)
 @Description			��ʼ���ӳٺ���
					��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���
					SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8
 @Input				SYSCLK	: ϵͳʱ��Ƶ��
 @Return				void
**********************************************************************************************************/
void Delay_Init(u8 SYSCLK)
{
#if SYSTEM_SUPPORT_OS													//�����Ҫ֧��OS
	u32 reload;
#endif
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);						//SysTickƵ��ΪHCLK
	fac_us = SYSCLK;													//�����Ƿ�ʹ��OS, fac_us����Ҫʹ��
#if SYSTEM_SUPPORT_OS													//�����Ҫ֧��OS
	reload = SYSCLK;													//ÿ���ӵļ������� ��λΪK
	reload *= 1000000 / delay_ostickspersec;								//����delay_ostickspersec�趨���ʱ��
																	//reloadΪ24λ�Ĵ���,���ֵ:16777216,��216M��,Լ��77.7ms����	
	fac_ms = 1000 / delay_ostickspersec;									//����OS������ʱ�����ٵ�λ
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;								//����SYSTICK�ж�
	SysTick->LOAD = reload;												//ÿ1/OS_TICKS_PER_SEC���ж�һ��
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;								//����SYSTICK
#endif
}

#if SYSTEM_SUPPORT_OS													//�����Ҫ֧��OS
/**********************************************************************************************************
 @Function			void Delay_US(u32 nus)
 @Description			��ʱnus
 @Input				nus : Ҫ��ʱ��us�� 0~204522252(���ֵ��2^32/fac_us@fac_us=21)
 @Return				void
**********************************************************************************************************/	    								   
void Delay_US(u32 nus)
{
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD;											//LOAD��ֵ
	
	ticks = nus * fac_us;												//��Ҫ�Ľ�����
	delay_osschedlock();												//��ֹOS����, ��ֹ���us��ʱ
	told = SysTick->VAL;												//�ս���ʱ�ļ�����ֵ
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow;									//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks) break;									//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�
		}
	}
	delay_osschedunlock();												//�ָ�OS����
}

/**********************************************************************************************************
 @Function			void Delay_MS(u16 nms)
 @Description			��ʱnms
 @Input				nms : Ҫ��ʱ��ms�� 0~65535
 @Return				void
**********************************************************************************************************/
void Delay_MS(u16 nms)
{
	if (delay_osrunning && delay_osintnesting == 0)							//���OS�Ѿ�������,���Ҳ������ж�����(�ж����治���������)
	{
		if (nms >= fac_ms)												//��ʱ��ʱ�����OS������ʱ������
		{
   			delay_ostimedly(nms / fac_ms);								//OS��ʱ
		}
		nms %= fac_ms;													//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ 
	}
	delay_us((u32)(nms*1000));											//��ͨ��ʽ��ʱ
}

#else																//����ucosʱ
/**********************************************************************************************************
 @Function			void Delay_US(u32 nus)
 @Description			��ʱnus
 @Input				nus : nus��ֵ��Ҫ����1000us
 @Return				void
**********************************************************************************************************/
void Delay_US(u32 nus)
{
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD;											//LOAD��ֵ
	
	ticks = nus * fac_us;												//��Ҫ�Ľ�����
	told = SysTick->VAL;												//�ս���ʱ�ļ�����ֵ
	
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow;									//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks) break;									//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�
		}
	}
}

/**********************************************************************************************************
 @Function			void Delay_MS(u16 nms)
 @Description			��ʱnms
 @Input				nms : Ҫ��ʱ��ms��
 @Return				void
**********************************************************************************************************/
void Delay_MS(u16 nms)
{
	u32 i;

	for (i = 0; i < nms; i++) {
		Delay_US(1000);
	}
}

#endif

/********************************************** END OF FLEE **********************************************/
