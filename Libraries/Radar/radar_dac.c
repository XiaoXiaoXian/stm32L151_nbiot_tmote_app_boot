/**
  *********************************************************************************************************
  * @file    rader_adc.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2017-10-31
  * @brief   
  *********************************************************************************************************
  * @attention
  *			
  *
  *
  *********************************************************************************************************
  */

#include "radar_dac.h"


DAC_HandleTypeDef 				DAC_Handler;								//DAC���

/**********************************************************************************************************
 @Function			void Rader_DAC_Init(void)
 @Description			�״�DAC��ʼ��
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_DAC_Init(void)
{
	DAC_ChannelConfTypeDef DAC_ChanelConfig;
	
	/* DAC��ʼ�� */
	DAC_Handler.Instance = DACx;
	HAL_DAC_Init(&DAC_Handler);
	
	/* DACͨ��������� */
	DAC_ChanelConfig.DAC_Trigger = DAC_TRIGGER_SOFTWARE;
	DAC_ChanelConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&DAC_Handler, &DAC_ChanelConfig, DACx_CHANNEL);
}

/**********************************************************************************************************
 @Function			void Rader_DAC_DeInit(void)
 @Description			�״�DAC��λ
 @Input				void
 @Return				void
**********************************************************************************************************/
void Rader_DAC_DeInit(void)
{
	HAL_DAC_DeInit(&DAC_Handler);
}

/********************************************** END OF FLEE **********************************************/
