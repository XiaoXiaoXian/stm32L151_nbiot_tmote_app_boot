/**
  *********************************************************************************************************
  * @file    stm32l1xx_config.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-11-01
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "stm32l1xx_config.h"
#include "hal_rtc.h"
#include "delay.h"


/**********************************************************************************************************
 @Function			static void LowPower_StopFront(void)
 @Description			����͹���Stopģʽǰ����(�ر�����)
 @Input				void
 @Return				void
**********************************************************************************************************/
static void LowPower_StopFront(void)
{	

}

/**********************************************************************************************************
 @Function			static void LowPower_StopFrontBehind(void)
 @Description			�˳��͹���Stopģʽ����(������������)
 @Input				void
 @Return				void
**********************************************************************************************************/
static void LowPower_StopFrontBehind(void)
{
	/* ϵͳʱ������ */
	Stm32_Clock_Init(RCC_PLLMUL_6, RCC_PLLDIV_3);
	
}

/**********************************************************************************************************
 @Function			void LowPower_Stop(void)
 @Description			����͹���Stopģʽ
 @Input				void
 @Return				void
**********************************************************************************************************/
void LowPower_Stop(void)
{
	LowPower_StopFront();												//����͹���Stopģʽǰ����
	
	__HAL_RCC_PWR_CLK_ENABLE();											//ʹ��PWRʱ��
	SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
	HAL_RTCEx_DeactivateWakeUpTimer(&RTC_Handler);
	HAL_RTCEx_SetWakeUpTimer_IT(&RTC_Handler, 0x800, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	uwTick += 1000;
	
	LowPower_StopFrontBehind();											//�˳��͹���Stopģʽ����
}



/********************************************** END OF FLEE **********************************************/
