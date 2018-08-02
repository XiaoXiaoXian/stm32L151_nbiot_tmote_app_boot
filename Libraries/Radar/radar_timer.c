/**
  *********************************************************************************************************
  * @file    rader_timer.c
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

#include "radar_timer.h"


TIM_HandleTypeDef				Radar_TIM2_Handler;							//�״ﶨʱ��2���

/**********************************************************************************************************
 @Function			void Radar_TIM2_Init(u16 arr, u16 psc)
 @Description			�״�ͨ�ö�ʱ��2�жϳ�ʼ��
 @Input				arr���Զ���װֵ
					psc��ʱ��Ԥ��Ƶ��
 @Other				��ʱ�����ʱ����㷽�� : Tout = ((arr+1)*(psc+1))/Ft us.
										Ft   = ��ʱ������Ƶ��,��λ:Mhz
					����ʹ�õ��Ƕ�ʱ��2!(��ʱ��2����APB1��, ʱ��ΪHCLK)
 @Return				void
**********************************************************************************************************/
void Radar_TIM2_Init(u16 arr, u16 psc)
{
	Radar_TIM2_Handler.Instance = TIM2;									//ͨ�ö�ʱ��2
	Radar_TIM2_Handler.Init.Prescaler = psc;								//��Ƶ��
	Radar_TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;					//���ϼ�����
	Radar_TIM2_Handler.Init.Period = arr;									//�Զ�װ��ֵ
	Radar_TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;				//ʱ�ӷ�Ƶ����
	HAL_TIM_Base_Init(&Radar_TIM2_Handler);
	
	HAL_TIM_Base_Start_IT(&Radar_TIM2_Handler);								//ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����ж� :��TIM_IT_UPDATE
}

/**********************************************************************************************************
 @Function			void Radar_TIM2_DeInit(void)
 @Description			�״�ͨ�ö�ʱ��2�жϸ�λ
 @Input				void
 @Return				void
**********************************************************************************************************/
void Radar_TIM2_DeInit(void)
{
	HAL_TIM_Base_DeInit(&Radar_TIM2_Handler);
}

/********************************************** END OF FLEE **********************************************/
